#pragma once

#include "core/features/variables.hpp"
#include "core/cheat/hooks/hooks.hpp"

namespace esp {
    void draw_esp (ImDrawList*);
    void draw_esp_grenade (ImDrawList*);

    inline void draw_healthbar (ImDrawList*, ImVec2, ImVec2, float);
    inline void draw_glow (ImDrawList*, const ImVec2&, const ImVec2&, ImColor, int, float, float);
    inline void draw_box (ImDrawList*, const ImVec2&, const ImVec2&, ImColor);
};