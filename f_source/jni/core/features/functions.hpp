#pragma once

#include "core/structs/sdk/originals.hpp"
#include "variables.hpp"

namespace utils {
    inline Vector3 get_pos (void* player)
    {
        return pointers::Transform::get_position (pointers::Component::get_transform(player));
    }

    inline int get_team (void* player)
    {
        return pointers::Player::get_team (player);
    }

    inline float get_health (void* player)
    {
        return *(float*) ((uint64_t)player + 0x2FC);
    }

    inline bool get_isMine (void* player)
    {
        return *(bool*) ((uint64_t)player + 0x1B4);
    }

    inline void set_obscuredint (uint64_t loc, int val)
    {
        int key = *(int*)loc;
        *(int*) (loc + 0x4) = val ^ key;
    }

    inline float get_distance (const Vector3& a, const Vector3& b)
    {
        Vector3 dist = b - a;

        return sqrtf (dist.x * dist.x + dist.y * dist.y + dist.z * dist.z);
    }

    inline bool InRadius (Vector2 point, Vector2 center, int radius)
    {
        return (pow(point.x - center.x, 2) + pow(point.y - center.y, 2)) <= pow (radius, 2);
    }

    inline bool IsVisible (const Vector3& from, const Vector3& to)
    {
        Vector3 origin = from;

        RaycastHit hit;

        float distance = get_distance (origin, to);

        Vector3 direction = (to - origin).normalized ();

        return !pointers::Physics::Raycast (origin, direction, hit, distance, -32767);
    }
};

namespace modifications {
    inline void weapon (void* weapon)
    {
        void* weapon_ptr = *(void**) ((uint64_t)weapon + 0xD8);

        if (weapon_ptr)
        {
            if (var.weapon.rapid_fire)
            {
                uint64_t rpm_ptr = (uint64_t)weapon_ptr + 0x24;

                utils::set_obscuredint (rpm_ptr, var.weapon.fire_rate);
                
                *(bool*) ((uint64_t)weapon_ptr + 0x179) = false;
            }

            if (var.weapon.ultimate_ammo)
            {
                uint64_t ammo_per_magazine = (uint64_t)weapon_ptr + 0x38;
                uint64_t suppressed_ammo = (uint64_t)weapon_ptr + 0x4C;
                uint64_t magazine_count = (uint64_t)weapon_ptr + 0x60;

                utils::set_obscuredint (ammo_per_magazine, var.weapon.ammo);
                utils::set_obscuredint (suppressed_ammo, var.weapon.ammo);
                utils::set_obscuredint (magazine_count, var.weapon.ammo);
            }
        }
    }

    inline void player (void* player_ptr)
    {
        if (var.weapon.shooting_grenade && pointers::Player::Weapon::get_shooting(player_ptr))
        {
            pointers::Player::Weapon::SpawnGrenade (player_ptr, (int)WeaponType::IncendiaryGrenade);
        }


        if (var.player.telekill)
        {
            for (auto& player : Players)
            {
                if (utils::get_health(player) <= 0.0f || utils::get_team(player) == utils::get_team(
                pointers::Player::my_player
            )) continue;

                Vector3 enemy_position = utils::get_pos (player);

                pointers::Transform::set_position (pointers::Component::get_transform(
                    pointers::Player::my_player
                ), enemy_position);
            }
        }

        if (var.player.masskill)
        {
            for (auto& player : Players)
            {
                if (utils::get_health(player) <= 0.0f || utils::get_team(player) == utils::get_team(
                pointers::Player::my_player
            )) continue;

                Vector3 my_position = utils::get_pos (pointers::Player::my_player);

                pointers::Transform::set_position (pointers::Component::get_transform(
                    player
                ), my_position);
            }
        }

        if (var.config.spam_chat)
        {
            pointers::Player::SendChatMessage (player_ptr, il2cpp_string_new(">@CheatsAndSources / @inffcheats"), true, true, true);
        }
    }

    inline void movement (void* player)
    {
        if (var.player.movement.speed_hack)
        {
            *(float*) ((uint64_t)player + 0x30) = var.player.movement.set_speed;
        }

        if (var.player.no_damage_of_fall)
        {
            *(float*) ((uint64_t)player + 0x78) = 0.0f;
        }

        if (var.player.movement.bunnyhop)
        {
            pointers::FirstPersonMovement::TryJump (player);

            *(float*) ((uint64_t)player + 0x4C) = var.player.movement.set_jump_speed;
        }
        

        if (var.player.movement.fly)
        {
            *(bool*) ((uint64_t)player + 0x38) = true;
        } else {
            *(bool*) ((uint64_t)player + 0x38) = false;
        }

        if (var.player.telekill_up)
        {
            for (auto& players : Players)
            {
                Vector3 enemy_pos = utils::get_pos (players);

                pointers::Transform::set_position (pointers::Component::get_transform(
                    pointers::Player::my_player
                ), Vector3 (enemy_pos.x, enemy_pos.y + 60.0f, enemy_pos.z));
            }
        }

        if (var.player.teleport_up)
        {
            pointers::Transform::set_position (pointers::Component::get_transform(
                pointers::Player::my_player
            ), Vector3 (0.0f, 60.0f, 0.0f));
        }
    }
};