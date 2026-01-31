#pragma once

#include <iostream>
#include <algorithm>

#include "esp.hpp"

void esp::draw_glow (ImDrawList* list, const ImVec2& min, const ImVec2& max, ImColor color, int layers, float spread, float intensity)
{
    for (int i = 1; i <= layers; ++i)
    {
        float a = (float) (layers - i) / layers * intensity;

        float glow = i * spread;

        list->AddRect (ImVec2(min.x - glow, min.y - glow), ImVec2(max.x + glow, max.y + glow),
        ImColor (color.Value.x, color.Value.y, color.Value.z, a));
    }
}

void esp::draw_healthbar(ImDrawList* list, ImVec2 box_min, ImVec2 box_max, float health)
{
    if (box_min.y > box_max.y)
    {
        std::swap(box_min.y, box_max.y);
    }

    float frac = ImClamp(health / 100.f, 0.f, 1.f);

    float box_h = box_max.y - box_min.y;

    float bar_w = ImClamp(box_h * 0.035f, 2.0f, 4.0f);
    float pad = 3.f;

    float x = box_min.x - bar_w - pad;

    float top = box_min.y;
    float bottom = box_max.y;

    float filled = box_h * frac;
    float fill_top = bottom - filled;

    ImColor col = frac > 0.6f ? ImColor(0,220,0) : frac > 0.3f ? ImColor(220,180,0) : ImColor(220,0,0);

    list->AddRectFilled(ImVec2(x, top), ImVec2(x + bar_w, bottom), IM_COL32(15,15,15,200));

    list->AddRectFilled(ImVec2(x, fill_top), ImVec2(x + bar_w, bottom), col);

    list->AddRect(ImVec2(x - 1, top - 1), ImVec2(x + bar_w + 1, bottom + 1), IM_COL32(0,0,0,220));

    char buffer[8];
    sprintf(buffer, "%d", (int)health);

    const float font_size = 9.5f;
    ImFont* font = ImGui::GetFont();

    ImVec2 text_size = font->CalcTextSizeA(font_size, FLT_MAX, 0.f, buffer);

    float text_x = x + bar_w * 0.5f - text_size.x * 0.5f;

    float color_height = bottom - fill_top;

    float text_y;

    if (color_height < text_size.y)
    {
        text_y = fill_top + color_height * 0.5f - text_size.y * 0.5f;
    }
    else
    {
        text_y = fill_top + 1.0f;
    }

    ImU32 outline = IM_COL32(0,0,0,220);

    if (health < 100)
    {
        list->AddText(font, font_size, ImVec2(text_x - 1, text_y), outline, buffer);
        list->AddText(font, font_size, ImVec2(text_x + 1, text_y), outline, buffer);
        list->AddText(font, font_size, ImVec2(text_x, text_y - 1), outline, buffer);
        list->AddText(font, font_size, ImVec2(text_x, text_y + 1), outline, buffer);

        list->AddText(font, font_size, ImVec2(text_x, text_y), IM_COL32(255,255,255,235), buffer);
    }
}

void esp::draw_box(ImDrawList* list, const ImVec2& box_min, const ImVec2& box_max, ImColor color)
{
    list->AddRect (box_min - ImVec2(1.f, 1.f), box_max + ImVec2(1.f, 1.f), IM_COL32 (0, 0, 0, 220), 0, 0, 1.5f);

    list->AddRect (box_min + ImVec2(1.f, 1.f), box_max - ImVec2(1.f, 1.f), IM_COL32 (0, 0, 0, 220), 0, 0, 1.5f);

    list->AddRect (box_min, box_max, color, 0, 0, 1.2f);
}