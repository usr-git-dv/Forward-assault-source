#pragma once

#include "ImGui/imgui_includes.hpp"

namespace ui {
    bool custom_sliderfloat (const char*, float*, float, float);
    bool custom_checkbox (const char*, bool*);
    bool custom_sliderint (const char*, int*, int, int);
};