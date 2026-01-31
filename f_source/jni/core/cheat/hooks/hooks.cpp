#include "hooks.hpp"

#include <fstream>

bool hooks::Physics::Raycast (Vector3 origin, Vector3 direction, RaycastHit& hit, float max_distance, int layermask)
{
    if (var.aim.silent_aim)
    {
        Vector3 new_origin = utils::get_pos (pointers::Camera::CameraManager::get_CameraManager(
            pointers::Player::my_player
        ));

        Vector3 near_target;

        float distance = FLT_MAX;
        
        bool has_target = false;

        for (auto& player : Players)
        {
            if (utils::get_health(player) <= 0.0f || utils::get_team(player) == utils::get_team(
                pointers::Player::my_player
            )) continue;

            void* bones = pointers::Player::Bones::get_bones (player);
            void* head = *(void**) ((uint64_t)bones + 0x20);

            Vector3 head_pos = utils::get_pos (head);

             if (var.aim.visible_check)
             {
                if (!utils::IsVisible (new_origin, head_pos)) continue;
             }

            float new_distance = (head_pos - new_origin).sqrMagnitude();

            if (new_distance < distance)
            {
                distance = new_distance;
                near_target = head_pos;
                has_target = true;
            }

            if (has_target)
            {
                direction = (near_target - new_origin).normalized();
            }
        }
    }

    if (var.weapon.wallshot)
    {
        layermask = 1 << 9;
    }

    return pointers::Physics::Raycast (origin, direction, hit, max_distance, layermask);
}

void hooks::Player::Update (void* player)
{
    if (player && utils::get_isMine(player))
    {
        pointers::Player::my_player = player;

        modifications::player (player);
    }
    
    if (!find_players(player)) Players.push_back(player);

    if (var.enable_chams)
    {
        ImVec4 player_color = utils::get_team (player) == utils::get_team (pointers::Player::my_player)
        ? var.team_color : var.enemy_color;

        ImVec4 glow_color = ImVec4 (player_color.x, player_color.y, player_color.z, 0.7f);

        monoArray <void**>* SkinnedMeshRender = *(monoArray<void**>**) ((uint64_t)player + 0x210);

        if (SkinnedMeshRender != NULL)
        {
            for (int i = 0; i < SkinnedMeshRender->getLength(); ++i)
            {
                void* object = SkinnedMeshRender->getPointer() [i];

                if (object != NULL)
                {
                    if (var.remove_texture)
                    {
                        pointers::Material::SetTexture (pointers::Renderer::get_material(object), il2cpp_string_new(
                            "_MainTex"
                        ), NULL);
                        pointers::Material::SetTexture (pointers::Renderer::get_material(object), il2cpp_string_new(
                            "_MetalicGlossMap"
                        ), NULL);
                    }

                    pointers::Material::SetShader (pointers::Renderer::get_material(object), pointers::Shader::Find(
                        il2cpp_string_new ("Standard")
                    ));

                    if (var.chams)
                    {
                        pointers::Material::SetShader (pointers::Renderer::get_material(object), pointers::Shader::Find(
                            il2cpp_string_new ("Hidden/Internal-Colored")
                        ));

                        pointers::Material::SetFloat (pointers::Renderer::get_material(object), il2cpp_string_new(
                            "_ZTest"
                        ), 8.0f);

                        pointers::Material::SetFloat (pointers::Renderer::get_material(object), il2cpp_string_new(
                            "_ZWrite"
                        ), 0.0f);

                        pointers::Material::SetFloat (pointers::Renderer::get_material(object), il2cpp_string_new(
                            "_Glossiness"
                        ), 0.5f);

                        pointers::Material::SetFloat (pointers::Renderer::get_material(object), il2cpp_string_new(
                            "_Metalic"
                        ), 0.6f);

                        pointers::Material::SetColor (pointers::Renderer::get_material(object), il2cpp_string_new(
                            "_Color"
                        ), Color(player_color.x, player_color.y, player_color.z, player_color.w));
                    }
                }
            }
        }
    }

    pointers::Player::Update (player);
}

void hooks::LocalPlayer::Update (void* localplayer)
{
    if (var.weapon.set_weapon)
    {
        pointers::LocalPlayer::SetWeapon (localplayer, weapon_id[var.weapon.select_weapon], true);

        var.weapon.set_weapon = false;
    }

    if (var.aim.trigger_bot)
    {
        for (auto& player : Players)
        {
            if (utils::get_health(player) <= 0 || utils::get_team(player) == utils::get_team(
                pointers::Player::my_player
            )) continue;

            void* bones = pointers::Player::Bones::get_bones (player);

            Vector3 target = utils::get_pos (player);

            Vector2 screen_pos = Vector2 (pointers::Camera::WorldToScreenPoint(pointers::Camera::CameraManager::get_CameraManager(
                pointers::Player::my_player
            ), target).x, var.y_dp - pointers::Camera::WorldToScreenPoint(pointers::Camera::CameraManager::get_CameraManager(
                pointers::Player::my_player
            ), target).y);

            Vector2 center = Vector2 (var.x_dp / 2, var.y_dp / 2);

            bool InFov = utils::InRadius (screen_pos, center, var.aim.trigger_bot_fov) && 
            pointers::Camera::WorldToScreenPoint (pointers::Camera::CameraManager::get_CameraManager(pointers::Player::my_player), target).z >= 0;

            if (var.aim.visible_check)
            {
                Vector3 my_camera = utils::get_pos (pointers::Camera::CameraManager::get_CameraManager(pointers::Player::my_player));

                if (!utils::IsVisible(my_camera, target)) continue;
            }

            if (var.aim.trigger_bot && InFov)
            {
                pointers::LocalPlayer::TryShoot (localplayer);
                break;
            }
        }
    }

    pointers::LocalPlayer::Update (localplayer);
}

void hooks::Grenade::Update (void* grenade)
{
    if (!find_grenades(grenade)) Grenades.push_back (grenade);

    if (var.weapon.teleport_grenade)
    {
        for (auto& player : Players)
        {
            if (utils::get_health(player) <= 0.0f || utils::get_team(player) == utils::get_team(
                pointers::Player::my_player
            )) continue;

            Vector3 enemy = utils::get_pos (player);

            void* transform_grenade = pointers::Component::get_transform (grenade);

            if (transform_grenade)
            {
                pointers::Transform::set_position (transform_grenade, enemy);
            }
        }
    }
    pointers::Grenade::Update (grenade);
}

void hooks::AudioManager::PlayAudioClipFromArray (void* sound, monoArray<void**>* clip, bool radio)
{
    if (var.player.test_sound)
    {
         monoArray<void**>* ct_win_sound = *(monoArray<void**>**) ((uint64_t)sound + 0xB8);

         clip = ct_win_sound;

        radio = false;
    }

    pointers::AudioManager::PlayAudioClipFromArray (sound, clip, radio);
}

void hooks::PhotonView::OnDestroy (void* player)
{
    Players.clear();

    pointers::PhotonView::OnDestroy (player);
}

void hooks::Grenade::OnDisable (void* grenade)
{
    Grenades.clear();

    pointers::Grenade::OnDisable (grenade);
}

void hooks::FirstPersonLook::Update (void* player)
{
    modifications::weapon (player);

    pointers::FirstPersonLook::Update (player);
}

void hooks::FirstPersonMovement::Update (void* player)
{
    modifications::movement (player);

    pointers::FirstPersonMovement::Update (player);
}

void hooks::SettingsRender::set_fog (bool set_fog)
{
    if (var.world.fog)
    {
        set_fog = true;
    }

    pointers::SettingsRender::set_fog (set_fog);
}

void hooks::SettingsRender::set_fogColor (Color set_colorFog)
{
    if (var.world.fog)
    {
        set_colorFog = Color (var.world.color_fog.x, var.world.color_fog.y, var.world.color_fog.z, var.world.color_fog.w);
    }
    pointers::SettingsRender::set_fogColor (set_colorFog);
}

void hooks::SettingsRender::set_fogDensity (float set_fogDensity)
{
    set_fogDensity = 0.03f;

    pointers::SettingsRender::set_fogDensity (set_fogDensity);
}

void hooks::SettingsRender::set_fogMode (int fog_mode)
{
    fog_mode = 2;

    pointers::SettingsRender::set_fogMode (fog_mode);
}

void hooks::SettingsRender::set_ambientMode (int ambient_mode)
{
    ambient_mode = 1;

    pointers::SettingsRender::set_ambientMode (ambient_mode);
}

void hooks::SettingsRender::set_ambientSkyColor (Color color)
{
    color = Color (var.world.color_fog.x, var.world.color_fog.y, var.world.color_fog.z, var.world.color_fog.w);

    pointers::SettingsRender::set_ambientSkyColor (color);
}

void hooks::GlobalDetectors::ObscuredDetected (void* obscured)
{
    if (var.config.bypass) return;

    pointers::GlobalDetectors::ObscuredDetected (obscured);
}

void hooks::GlobalDetectors::SpeedDetected (void* speed)
{
    if (var.config.bypass) return;

    pointers::GlobalDetectors::SpeedDetected (speed);
}

void hooks::GlobalDetectors::TimeDetected (void* time)
{
    if (var.config.bypass) return;

    pointers::GlobalDetectors::TimeDetected (time);
}

void hooks::GlobalDetectors::WallDetected (void* wall)
{
    if (var.config.bypass) return;

    pointers::GlobalDetectors::WallDetected (wall);
}

void hooks::GlobalDetectors::RadarDetected (void* radar)
{
    if (var.config.bypass) return;

    pointers::GlobalDetectors::RadarDetected (radar);
}

void hooks::GlobalDetectors::RecoilDetected (void* recoil)
{
    if (var.config.bypass) return;

    pointers::GlobalDetectors::RecoilDetected (recoil);
}