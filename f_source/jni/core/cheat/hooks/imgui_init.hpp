#pragma once

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <algorithm>
#include <sys/system_properties.h>

#include "core/visuals/menu/menu.hpp"
#include "core/visuals/esp/esp.hpp"

bool setup = false;

void (*Input) (void*);
void hook_Input (void* touch)
{
    Input (touch);
    ImGui_ImplAndroid_HandleInputEvent ((AInputEvent*)touch);
}

void setup_imgui ()
{
    char value [PROP_VALUE_MAX];
    float dpi_scale = 1.0f;
    if (__system_property_get("ro.sf.lcd_density", value) > 0) dpi_scale = atoi (value) / 160.f;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplOpenGL3_Init ("#version 300 es");

    ImGuiIO& io = ImGui::GetIO();

    io.Fonts->Clear();

    ImFont* bold_font = io.Fonts->AddFontFromFileTTF ("/system/fonts/SourceSansPro-Bold.ttf", 26.5f, nullptr, io.Fonts->GetGlyphRangesCyrillic());

    io.Fonts->Build();

    ImGui::GetStyle().ScaleAllSizes (dpi_scale);

    io.DisplayFramebufferScale = ImVec2 (dpi_scale, dpi_scale);
}

EGLBoolean (*EglSwapBuffers) (EGLDisplay dpy, EGLSurface surface);
EGLBoolean hook_EglSwapBuffers (EGLDisplay dpy, EGLSurface surface)
{
    eglQuerySurface (dpy, surface, EGL_WIDTH, &var.x_dp);
    eglQuerySurface (dpy, surface, EGL_HEIGHT, &var.y_dp);

    if (!setup)
    {
        setup_imgui ();
        setup = true;
    }

    ImGui_ImplOpenGL3_NewFrame ();
    ImGui_ImplAndroid_NewFrame (var.x_dp, var.y_dp);
    ImGui::NewFrame ();

    gui::render_menu ();
    gui::draw_open_button ();

    esp::draw_esp (ImGui::GetBackgroundDrawList());
    esp::draw_esp_grenade (ImGui::GetBackgroundDrawList());

    ImGui::Render ();
    ImGui::EndFrame();

    glViewport(0, 0, var.x_dp, var.y_dp);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    return EglSwapBuffers(dpy, surface);
}

void init_symbols ()
{
    DobbyHook(DobbySymbolResolver("libEGL.so", "eglSwapBuffers"), (void*)hook_EglSwapBuffers, (void**)&EglSwapBuffers);
    DobbyHook(DobbySymbolResolver("libinput.so", "_ZN7android11MotionEvent8copyFromEPKS0_b"), (void*)hook_Input, (void**)&Input);
}