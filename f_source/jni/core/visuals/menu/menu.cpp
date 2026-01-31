#include "menu.hpp"

void gui::draw_open_button ()
{
    style_menu();
    ImGui::SetNextWindowSize (ImVec2(120, 130));
    if (ImGui::Begin("behin", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar))
    {
        if (ImGui::Button("Open", ImVec2(80, 80)))
        {
            var.open_menu = !var.open_menu;
        }
    }
    ImGui::End();
}

void gui::render_menu ()
{
    style_menu();

    ImGui::SetNextWindowSize (ImVec2(1142, 615));

    if (var.open_menu)
    {
        if (ImGui::Begin("test", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize))
        {
            ImGui::BeginChild ("Tabs", ImVec2 (140.0f, 0), true);
            {
                if (ImGui::Button("Visuals", ImVec2 (-1, 70)))
                {
                    var.tabs = 0;
                }

                ImGui::Dummy (ImVec2(0, 2));

                if (ImGui::Button("Aim", ImVec2 (-1, 70)))
                {
                    var.tabs = 1;
                }

                ImGui::Dummy (ImVec2(0, 2));

                if (ImGui::Button("Player", ImVec2(-1, 70)))
                {
                    var.tabs = 2;
                }

                ImGui::Dummy (ImVec2(0, 2));

                if (ImGui::Button("Weapon", ImVec2 (-1, 70)))
                {
                    var.tabs = 3;
                }
            }
            ImGui::EndChild ();
            ImGui::SameLine (0, 15.664f);

            ImGui::BeginChild ("Main child", ImVec2(400, 0), true);
            {
                switch (var.tabs)
                {
                    case 0:
                    {
                        ImGui::SeparatorText ("Esp");

                        ui::custom_checkbox ("test sound", &var.player.test_sound);
                        
                        ui::custom_checkbox ("Enable esp", &var.esp.esp);

                        ImGui::Separator ();

                        ui::custom_checkbox ("Box", &var.esp.esp_box);
                        ImGui::Separator ();

                        ui::custom_checkbox ("Health", &var.esp.esp_health);

                        ImGui::Separator ();

                        ui::custom_checkbox ("Nickname", &var.esp.esp_nickname);

                        ImGui::Separator ();

                        ui::custom_checkbox ("Weapon", &var.esp.esp_weapon);

                        if (var.esp.esp_weapon)
                        {
                            ui::custom_checkbox ("Grenade", &var.esp.esp_grenade);

                            ImGui::Separator ();
                        }

                        ui::custom_checkbox ("Chams", &var.enable_chams);

                        if (var.enable_chams)
                        {
                            ui::custom_checkbox ("Remove texture", &var.remove_texture);

                            ImGui::Separator ();

                            ui::custom_checkbox ("Enable", &var.chams);
                        }
                        ImGui::SeparatorText ("World");

                        ui::custom_checkbox ("Enable fog", &var.world.fog);

                        break;
                    }

                    case 1:
                    {
                        ImGui::SeparatorText ("Aim");

                        ui::custom_checkbox ("Silent aim", &var.aim.silent_aim);

                        if (var.aim.silent_aim)
                        {
                            ui::custom_checkbox ("Visible check", &var.aim.visible_check);

                            ImGui::Separator ();

                            ui::custom_checkbox ("Trigger bot", &var.aim.trigger_bot);

                            ImGui::Separator ();

                            if (var.aim.trigger_bot)
                            {
                                ui::custom_checkbox ("Trigger bot fov", &var.aim.trigger_fov);
                                
                                if (var.aim.trigger_fov)
                                {
                                    ui::custom_sliderfloat ("Set fov", &var.aim.trigger_bot_fov, 0.0f, 360.0f);
                                }
                            }
                        }

                        ImGui::Separator ();

                        ui::custom_checkbox ("Wallshot", &var.weapon.wallshot);

                        break;
                    }

                    case 2:
                    {
                        ImGui::SeparatorText ("Player");

                        ui::custom_checkbox ("Telekill", &var.player.telekill);

                        ImGui::Separator ();
                    
                        ui::custom_checkbox ("Masskill", &var.player.masskill);

                        ImGui::Separator ();

                        ui::custom_checkbox ("Telekill up", &var.player.telekill_up);

                        ImGui::Separator ();

                        ui::custom_checkbox ("Teleport up", &var.player.teleport_up);

                        ImGui::Separator ();

                        ui::custom_checkbox ("Fly", &var.player.movement.fly);

                        ImGui::Separator ();

                        ui::custom_checkbox ("Speed hack", &var.player.movement.speed_hack);

                        ImGui::Separator ();

                        ui::custom_checkbox ("No damage of fall", &var.player.no_damage_of_fall);

                        ImGui::Separator ();

                        ui::custom_checkbox ("Bunnyhop", &var.player.movement.bunnyhop);

                        ImGui::Separator ();

                        ui::custom_checkbox ("Spam chat", &var.config.spam_chat);

                        break;
                    }

                    case 3:
                    {
                        ImGui::SeparatorText ("Weapon");

                        ui::custom_checkbox ("Ultimate ammo", &var.weapon.ultimate_ammo);

                        ImGui::Separator ();

                        ui::custom_checkbox ("Rapid fire", &var.weapon.rapid_fire);

                        ImGui::Separator ();

                        ui::custom_checkbox ("Shooting grenade", &var.weapon.shooting_grenade);

                        ImGui::Separator ();

                        ui::custom_checkbox ("Nuke players", &var.weapon.teleport_grenade);

                        break;
                    }
                }
            }

            ImGui::EndChild ();
            ImGui::SameLine (0, 20.934f);

            ImGui::BeginChild ("Settings child", ImVec2(0, 0), true);
            {
                switch (var.tabs)
                {
                    case 0:
                    {
                        ImGui::SeparatorText ("Esp settings");

                        ImGui::ColorEdit4 ("Color filled box", (float*)&var.filled_box_color);

                        ImGui::Separator ();

                        if (var.remove_texture)
                        {
                            ImGui::ColorEdit4 ("Chams enemy color", (float*)&var.enemy_color);

                            ImGui::Separator ();

                            ImGui::ColorEdit4 ("Chams team color", (float*)&var.team_color);
                        }

                        ImGui::SeparatorText ("World settings");

                        ImGui::ColorEdit4 ("Fog color", (float*)&var.world.color_fog);

                        break;
                    }

                    case 1:
                    {
                        ImGui::SeparatorText ("Aim settings");

                        break;
                    }

                    case 2:
                    {
                        ImGui::SeparatorText ("Player settings");

                        if (var.player.movement.speed_hack)
                        {
                            ui::custom_sliderfloat ("Set speed", &var.player.movement.set_speed, 0.0f, 50.0f);

                            ImGui::Separator ();
                        }

                        if (var.player.movement.bunnyhop)
                        {
                            ui::custom_sliderfloat ("Set speed jump", &var.player.movement.set_jump_speed, 0.0f, 40.0f);
                        }

                        break;
                    }

                    case 3:
                    {
                        ImGui::SeparatorText ("Weapon settings");

                        if (var.weapon.ultimate_ammo)
                        {
                            ui::custom_sliderint ("Set ammo", &var.weapon.ammo, 0, 99999);

                            ImGui::Separator ();
                        }

                        if (var.weapon.rapid_fire)
                        {
                            ui::custom_sliderint ("Set fire rate", &var.weapon.fire_rate, 0, 4000);

                            ImGui::Separator ();
                        }

                        
                        ImGui::Combo ("Weapons", &var.weapon.select_weapon, weapon_names, IM_ARRAYSIZE(weapon_names));

                        ImGui::Separator ();

                        if (ImGui::Button("Set"))
                        {
                            var.weapon.set_weapon = true;
                        }

                        break;
                    }
                }
            }

            ImGui::EndChild();
        }

        ImGui::End();
    }
}