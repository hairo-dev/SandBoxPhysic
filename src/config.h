#pragma once

#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <random>

const float Window_Width = 1200;
const float Window_Height = 720;

inline Vector2 &operator+=(Vector2 &vec1,const Vector2 vec2){
    vec1.x += vec2.x;
    vec1.y += vec2.y;
    return vec1;
}

inline Vector2 &operator*=(Vector2 &vec1,const Vector2 vec2) {
    vec1.x *= vec2.x;
    vec1.y *= vec2.y;
    return vec1;
}

