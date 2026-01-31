#pragma once

#include "core/visuals/esp/esp.hpp"

inline void style_menu ()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    style.WindowRounding = 10.f;
    style.FrameRounding = 6.f;
    style.PopupRounding = 6.f;
    style.WindowBorderSize = 0.0f;
    style.ChildRounding = 10.f;
    style.ChildBorderSize = 0.0f;

    style.WindowPadding = ImVec2 (12, 12);
    style.FramePadding = ImVec2 (10, 6);
    style.ItemSpacing = ImVec2 (8, 8);

    colors[ImGuiCol_WindowBg] = ImVec4 (0.06f, 0.06f, 0.06f, 1.0f);
    colors[ImGuiCol_ChildBg] = ImVec4 (0.09f, 0.09f, 0.09f, 1.0f);
    colors[ImGuiCol_FrameBg] = ImVec4 (0.15f, 0.15f, 0.15f, 1.0f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4 (0.20f, 0.20f, 0.20f, 1.0f);
    colors[ImGuiCol_FrameBgActive] = ImVec4 (0.25f, 0.25f, 0.25f, 1.0f);
    colors[ImGuiCol_Button] = ImVec4 (0.0745f, 0.0745f, 0.0745f, 1.0f);
}