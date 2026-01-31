#pragma once

#include <cmath>

#include "core/searcher/searcher.hpp"

struct Vector2 {
    float x, y = 0;

    Vector2 (float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    Vector2() = default;
};

struct Vector3 {
    float x, y, z = 0.0f;

    Vector3 (float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3 () = default;

    Vector3 operator - (const Vector3& other) const 
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    float magnitude() const
    {
        return std::sqrt (x * x + y * y + z * z);
    }

    float sqrMagnitude() const
    {
        return x * x + y * y + z * z;
    }

    Vector3 operator / (float scalar) const 
    {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    Vector3 normalized() const 
    {
        float mag = magnitude();
        return mag > 0 ? *this / mag : Vector3();
    }
};