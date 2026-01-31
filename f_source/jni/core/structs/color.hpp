#pragma once

struct Color {
    float r, g, b, a = 0.0f;

    Color (float r, float g, float b, float a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    Color() = default;
};
