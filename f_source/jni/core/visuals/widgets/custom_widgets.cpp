#include "custom_widgets.hpp"

bool ui::custom_checkbox (const char* label, bool* value)
{
    ImGui::PushStyleColor (ImGuiCol_CheckMark, ImVec4(0.0f, 0.7f, 0.0f, 1.0f));
    ImGui::PushStyleColor (ImGuiCol_FrameBg, ImVec4 (0.2f, 0.2f, 0.2f, 1.0f));

    bool new_checkbox = ImGui::Checkbox (label, value);

    ImGui::PopStyleColor (2);

    return new_checkbox;
}

bool ui::custom_sliderint (const char* label, int* value, int min, int max)
{
    ImGui::PushStyleColor (ImGuiCol_SliderGrab, ImColor(255, 255, 255, 140).Value);
    ImGui::PushStyleVar (ImGuiStyleVar_FrameBorderSize, 0.0f);

    bool new_slider = ImGui::SliderInt (label, value, min, max);

    ImGui::PopStyleVar ();
    ImGui::PopStyleColor ();

    return new_slider;
}

bool ui::custom_sliderfloat (const char* label, float* value, float min, float max)
{
    ImGui::PushStyleColor (ImGuiCol_SliderGrab, ImColor(255, 255, 255, 140).Value);
    ImGui::PushStyleVar (ImGuiStyleVar_FrameBorderSize, 0.0f);

    bool new_slider = ImGui::SliderFloat (label, value, min, max);

    ImGui::PopStyleVar ();
    ImGui::PopStyleColor ();

    return new_slider;
}