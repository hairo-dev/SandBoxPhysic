#pragma once
#include "config.h"

typedef enum {
    BODY_STATIC,       // Harita, duvar, zemin
    BODY_KINEMATIC,    // Oyuncu, hareketli platform 
    BODY_DYNAMIC       // Düşen toplar, çarpışan objeler 
} BodyType;

struct Ball{
    Color color;
    BodyType type;
    float radius;
    Vector2 position;
    Vector2 velocity;

    bool isGrounded = false;
    bool isSleeping = true;

    Ball(Vector2 position,Vector2 velocity,float radius,Color color,BodyType type){
        this->position = position;
        this->velocity = velocity;
        this->radius = radius;
        this->color = color;
        this->type = type;
    }
};

