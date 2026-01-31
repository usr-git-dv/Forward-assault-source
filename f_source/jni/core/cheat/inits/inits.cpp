#include "inits.hpp"

#define Hook(offset,ptr,orig) DobbyHook((void*)memory::get_address("libil2cpp.so",offset),(void*)ptr,(void**)&orig)

void cheat ()
{
    do {
        sleep (1);
    } while (!memory::lib_loaded("libil2cpp.so"));

    Hook (0x3B9FA0, hooks::Player::Update, pointers::Player::Update);
    Hook (0x3A5878, hooks::FirstPersonLook::Update, pointers::FirstPersonLook::Update);
    Hook (0x595048, hooks::Grenade::Update, pointers::Grenade::Update);
    Hook (0x3A7454, hooks::FirstPersonMovement::Update, pointers::FirstPersonMovement::Update);
    Hook (0x3CE3E8, hooks::LocalPlayer::Update, pointers::LocalPlayer::Update);
    Hook (0x594734, hooks::Grenade::OnDisable, pointers::Grenade::OnDisable);
    Hook (0x543D74, hooks::PhotonView::OnDestroy, pointers::PhotonView::OnDestroy);
    Hook (0x1C94640, hooks::Physics::Raycast, pointers::Physics::Raycast);

    Hook (0x4A2CC0, hooks::GlobalDetectors::ObscuredDetected, pointers::GlobalDetectors::ObscuredDetected);
    Hook (0x4A2CE4, hooks::GlobalDetectors::SpeedDetected, pointers::GlobalDetectors::SpeedDetected);
    Hook (0x4A2D08, hooks::GlobalDetectors::TimeDetected, pointers::GlobalDetectors::TimeDetected);
    Hook (0x4A2D0C, hooks::GlobalDetectors::WallDetected, pointers::GlobalDetectors::WallDetected);
    Hook (0x4A2D30, hooks::GlobalDetectors::RadarDetected, pointers::GlobalDetectors::RadarDetected);
    Hook (0x4A2D74, hooks::GlobalDetectors::RecoilDetected, pointers::GlobalDetectors::RecoilDetected);

    Hook (0x1C2E394, hooks::SettingsRender::set_fog, pointers::SettingsRender::set_fog);
    Hook (0x1C2E490, hooks::SettingsRender::set_fogColor, pointers::SettingsRender::set_fogColor);
    Hook (0x1C2E538, hooks::SettingsRender::set_fogDensity, pointers::SettingsRender::set_fogDensity);
    Hook (0x1C2E3D0, hooks::SettingsRender::set_fogMode, pointers::SettingsRender::set_fogMode);
    Hook (0x1C2E598, hooks::SettingsRender::set_ambientMode, pointers::SettingsRender::set_ambientMode);
    Hook (0x1C2E658, hooks::SettingsRender::set_ambientSkyColor, pointers::SettingsRender::set_ambientSkyColor);

    Hook (0x583864, hooks::AudioManager::PlayAudioClipFromArray, pointers::AudioManager::PlayAudioClipFromArray);

    pointers::Player::Bones::get_bones = (decltype(pointers::Player::Bones::get_bones)) memory::get_address ("libil2cpp.so", 0x3AC314);
    pointers::Player::Weapon::get_shooting = (decltype(pointers::Player::Weapon::get_shooting)) memory::get_address ("libil2cpp.so", 0x3AD494);
    pointers::Player::Weapon::SpawnGrenade = (decltype(pointers::Player::Weapon::SpawnGrenade)) memory::get_address ("libil2cpp.so", 0x3BAA9C);
    pointers::Player::get_team = (decltype(pointers::Player::get_team)) memory::get_address ("libil2cpp.so", 0x3ABD6C);
    pointers::Player::SendChatMessage = (decltype(pointers::Player::SendChatMessage)) memory::get_address ("libil2cpp.so", 0x3ADB48);
    pointers::Player::get_username = (decltype(pointers::Player::get_username)) memory::get_address ("libil2cpp.so", 0x3AB468);
    pointers::Player::set_visible = (decltype(pointers::Player::set_visible)) memory::get_address ("libil2cpp.so", 0x3AD1B0);

    pointers::Transform::get_position = (decltype(pointers::Transform::get_position)) memory::get_address ("libil2cpp.so", 0x1C536F8);
    pointers::Transform::set_position = (decltype(pointers::Transform::set_position)) memory::get_address ("libil2cpp.so", 0x1C53798);
    pointers::Component::get_transform = (decltype(pointers::Component::get_transform)) memory::get_address ("libil2cpp.so", 0x1C47D7C);

    pointers::Camera::WorldToScreenPoint = (decltype(pointers::Camera::WorldToScreenPoint)) memory::get_address ("libil2cpp.so", 0x1C22604);
    pointers::Camera::CameraManager::get_CameraManager = (decltype(pointers::Camera::CameraManager::get_CameraManager)) memory::get_address ("libil2cpp.so", 0x58964C);

    pointers::Shader::Find = (decltype(pointers::Shader::Find)) memory::get_address ("libil2cpp.so", 0x1C2E944);

    pointers::Material::SetTexture = (decltype(pointers::Material::SetTexture)) memory::get_address ("libil2cpp.so", 0x1C2F708);
    pointers::Material::SetColor = (decltype(pointers::Material::SetColor)) memory::get_address ("libil2cpp.so", 0x1C2F40C);
    pointers::Material::SetFloat = (decltype(pointers::Material::SetFloat)) memory::get_address ("libil2cpp.so", 0x1C30578);
    pointers::Material::SetShader = (decltype(pointers::Material::SetShader)) memory::get_address ("libil2cpp.so", 0x1C2F1D0);

    pointers::Renderer::get_material = (decltype(pointers::Renderer::get_material)) memory::get_address ("libil2cpp.so", 0x1C2E230);

    pointers::FirstPersonMovement::TryJump = (decltype(pointers::FirstPersonMovement::TryJump)) memory::get_address ("libil2cpp.so", 0x3A5E54);

    pointers::LocalPlayer::TryShoot = (decltype(pointers::LocalPlayer::TryShoot)) memory::get_address ("libil2cpp.so", 0x3C616C);
    pointers::LocalPlayer::SetWeapon = (decltype(pointers::LocalPlayer::SetWeapon)) memory::get_address ("libil2cpp.so", 0x3CA21C);
}