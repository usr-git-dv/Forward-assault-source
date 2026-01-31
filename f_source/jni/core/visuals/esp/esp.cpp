#include "draw_utils.hpp"

void esp::draw_esp (ImDrawList* list)
{
    if (var.aim.trigger_fov)
    {
        list->AddCircle (ImVec2(var.x_dp / 2, var.y_dp / 2), var.aim.trigger_bot_fov, ImColor(255, 255, 255, 255), 64, 1.2f);
    }
    
    if (var.esp.esp)
    {
        for (auto& player : Players)
        {
            if (utils::get_health(player) <= 0.0f || utils::get_team(player) == utils::get_team(
                pointers::Player::my_player
            )) continue;
            
            Vector3 player_pos = utils::get_pos(player);
            Vector3 pos = pointers::Camera::WorldToScreenPoint (pointers::Camera::CameraManager::get_CameraManager(
                pointers::Player::my_player), player_pos);

            void* bones = pointers::Player::Bones::get_bones (player);

            void* head = *(void**) ((uint64_t)bones + 0x20);
            void* hips = *(void**) ((uint64_t)bones + 0x30);
            void* left_lower_leg = *(void**) ((uint64_t)bones + 0x60);
            void* right_lower_leg = *(void**) ((uint64_t) bones + 0x70);

            Vector3 head_pos = utils::get_pos (head);
            Vector3 hips_pos = utils::get_pos (hips);
            Vector3 left_leg = utils::get_pos (left_lower_leg);
            Vector3 right_leg = utils::get_pos (right_lower_leg);

            Vector3 w_head = pointers::Camera::WorldToScreenPoint (pointers::Camera::CameraManager::get_CameraManager(pointers::Player::my_player), head_pos);
            Vector3 w_hips = pointers::Camera::WorldToScreenPoint (pointers::Camera::CameraManager::get_CameraManager(pointers::Player::my_player), hips_pos);
            Vector3 w_left_leg = pointers::Camera::WorldToScreenPoint (pointers::Camera::CameraManager::get_CameraManager(pointers::Player::my_player), left_leg);
            Vector3 w_right_leg = pointers::Camera::WorldToScreenPoint (pointers::Camera::CameraManager::get_CameraManager(pointers::Player::my_player), right_leg);
        
            if (w_head.z < 0.0001f && w_hips.z < 0.0001f) continue;

            ImVec2 screen_head (w_head.x, var.y_dp - w_head.y);
            ImVec2 screen_hips (w_hips.x, var.y_dp - w_hips.y);
            ImVec2 screen_left_foot (w_left_leg.x, var.y_dp - w_left_leg.y);
            ImVec2 screen_right_foot (w_right_leg.x, var.y_dp - w_right_leg.y);

            ImVec2 screen_feet ((screen_left_foot.x + screen_right_foot.x) * 0.5f, (screen_left_foot.y + screen_right_foot.y) * 0.5f);

            float height = std::fabs (screen_head.y - screen_feet.y);
            float width = height * 0.52f;

            float vertical_offset = height * 0.632f;
            float vertical_hips_offset = height * 0.205f;

            ImVec2 box_min (screen_hips.x - width, screen_feet.y + vertical_offset);
            ImVec2 box_max (screen_hips.x + width, screen_head.y - vertical_hips_offset);

            if (var.esp.esp_box)
            {
                esp::draw_box (list, box_min, box_max, ImColor(255, 255, 255, 255));
            }

            if (var.esp.esp_filled)
            {
                list->AddRectFilled (box_min, box_max, var.filled_box_color, 0, 0);
            }

            if (var.esp.esp_health)
            {
                esp::draw_healthbar (list, box_min, box_max, utils::get_health(player));
            }

            if (var.esp.esp_nickname)
            {
                MonoString* nickname = pointers::Player::get_username (player);

                if (nickname != nullptr && nickname->get_length() > 0)
                {
                    std::string name = nickname->get_string ();

                    const float font_size = 10.5f;

                    ImFont* font = ImGui::GetFont ();

                    ImVec2 text_size = font->CalcTextSizeA (font_size, FLT_MAX, 0.0f, name.c_str());

                    float center_x = (box_min.x + box_max.x) * 0.5f;

                    ImVec2 text_pos (center_x - text_size.x * 0.5f, box_max.y - text_size.y - 3.0f);

                    ImU32 outline = IM_COL32 (0, 0, 0, 200);

                    list->AddText (font, font_size, text_pos + ImVec2 (-1, 0), outline, name.c_str());
                    list->AddText (font, font_size, text_pos + ImVec2 (1, 0), outline, name.c_str());
                    list->AddText (font, font_size, text_pos + ImVec2 (0, -1), outline, name.c_str());
                    list->AddText (font, font_size, text_pos + ImVec2 (0, 1), outline, name.c_str());

                    list->AddText (font, font_size, text_pos, IM_COL32(255, 255, 255, 255), name.c_str());
                }
            }

            if (var.esp.esp_weapon)
            {
                void* ThirdPersonWeapon = *(void**) ((uint64_t)player + 0x200);
                void* Weapon = *(void**) ((uint64_t)ThirdPersonWeapon + 0x38);
                MonoString* name = *(MonoString**) ((uint64_t)Weapon + 0x18);

                if (name != nullptr && name->get_length() > 0)
                {
                    std::string name_weapon = name->get_string ();

                    const float font_size = 10.5f;

                    ImFont* font = ImGui::GetFont ();

                    ImVec2 text_size = font->CalcTextSizeA (font_size, FLT_MAX, 0.0f, name_weapon.c_str());

                    float center_x = (box_min.x + box_max.x) * 0.5f;

                    ImVec2 text_pos (center_x - text_size.x * 0.5f, box_min.y - text_size.y + 11.550f);

                    ImU32 outline = IM_COL32 (0, 0, 0, 200);

                    list->AddText (font, font_size, text_pos + ImVec2 (-1, 0), outline, name_weapon.c_str());
                    list->AddText (font, font_size, text_pos + ImVec2 (1, 0), outline, name_weapon.c_str());
                    list->AddText (font, font_size, text_pos + ImVec2 (0, -1), outline, name_weapon.c_str());
                    list->AddText (font, font_size, text_pos + ImVec2 (0, 1), outline, name_weapon.c_str());

                    list->AddText (font, font_size, text_pos, IM_COL32(255, 255, 255, 255), name_weapon.c_str());
                }
            }
        }
    }
}

void esp::draw_esp_grenade (ImDrawList* list)
{
    if (var.esp.esp_grenade)
    {
        for (auto& grenade : Grenades)
        {
            Vector3 grenade_pos = utils::get_pos (grenade);

            Vector3 world_position_grenade = pointers::Camera::WorldToScreenPoint (pointers::Camera::CameraManager::get_CameraManager (
                pointers::Player::my_player
            ), grenade_pos);

            if (world_position_grenade.z < 0.001f) continue;

            ImVec2 point (world_position_grenade.x, var.y_dp - world_position_grenade.y);

            list->AddCircleFilled (point, 3.0f, ImColor (255, 0, 0, 210), 0);
        }
    }
}