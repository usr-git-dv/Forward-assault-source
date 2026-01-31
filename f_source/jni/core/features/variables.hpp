#pragma once

#include "core/visuals/widgets/custom_widgets.hpp"

struct variables {
    
    struct Esp {
        bool esp, esp_box, esp_filled,
            esp_health, esp_nickname, esp_weapon,
                esp_grenade = false;  
    } esp;

    struct Player {
        bool telekill, masskill, telekill_up,
            teleport_up, test_sound, no_damage_of_fall = false;

        float set_speed = 0.0f;

        struct Movement {
            bool speed_hack, fly, bunnyhop = false;

            float set_speed, set_jump_speed = 0.0f;
        } movement;
    } player;

    struct Weapon {
        bool rapid_fire, ultimate_ammo, shooting_grenade,
            teleport_grenade, wallshot, set_weapon = false;

        int fire_rate, ammo = 9999999;

        float spread = 0.0f;

        int select_weapon = 0;
    } weapon;

    struct World {
        bool fog = false;

        ImVec4 color_fog;

        float density = 0.0f;
    } world;

    struct Aim {
        bool silent_aim, visible_check, trigger_bot,
            trigger_fov = false;

        float trigger_bot_fov = 0.0f;

    } aim;

    struct Config {
        bool spam_chat = false;

        bool bypass = true;
    } config;

    bool remove_texture, enable_chams, chams = false;

    int x_dp, y_dp = 0;

    ImColor filled_box_color;
    ImVec4 team_color, enemy_color;

    bool open_menu = false;

    int tabs = 0;

} inline var;