#pragma once
#include "config.h"
#include "Entity.h"

const float gravity = 9.36;

void OnGravity(Ball &entity,float &deltatime){
    if(entity.type == BodyType::BODY_DYNAMIC){
        entity.velocity.y += gravity * deltatime;
    }
}

void collision_detect(std::vector<Ball*>& entities, float deltaTime)
{
    for (size_t i = 0; i < entities.size(); ++i)
    {
        for (size_t j = 0; j < entities.size(); j++)
        {
            if(i == j) continue;

            Ball* a = entities[i];
            Ball* b = entities[j];

            if(a->type == BodyType::BODY_DYNAMIC && b->type == BodyType::BODY_DYNAMIC){

            Vector2 delta = Vector2Subtract(b->position, a->position);
            float dist = Vector2Length(delta);
            float minDist = a->radius + b->radius;

            if (dist >= minDist || dist < 0.0001f) 
                continue;

            Vector2 normal = Vector2Scale(delta, 1.0f / dist);

            float penetration = minDist - dist;

            Vector2 correction = Vector2Scale(normal, penetration * 0.5f);
            a->position = Vector2Subtract(a->position, correction);
            b->position = Vector2Add(b->position, correction);

            Vector2 relativeVelocity = Vector2Subtract(b->velocity, a->velocity);
            float velAlongNormal = Vector2DotProduct(relativeVelocity, normal);

            if (velAlongNormal > 0) 
                continue;

            float impulse = -velAlongNormal;  

            Vector2 impulseVec = Vector2Scale(normal, impulse);

            
                a->velocity = Vector2Subtract(a->velocity, impulseVec);
                b->velocity = Vector2Add(b->velocity, impulseVec);
            
                if(Vector2Length(a->velocity) < 0.01f){
                    a->velocity = Vector2{0.0f,0.0f};
                    a->velocity *= pow(0.55f, deltaTime);
                }
                if(Vector2Length(b->velocity) < 0.01f){
                    b->velocity = Vector2{0.0f,0.0f};
                    b->velocity *= pow(0.55f, deltaTime);
                }

            }

            ////////////////////////////////////////////////////////////////////////////

            if(a->type == BodyType::BODY_DYNAMIC && b->type == BodyType::BODY_STATIC){
                Vector2 b_to_a = Vector2Subtract(a->position,b->position);
                Vector2 surface_normal = Vector2Normalize(b_to_a);
                float distance = Vector2Length(b_to_a);
                float min_distance = a->radius + b->radius;

                if(distance > min_distance) continue;

                float penetration_length = min_distance - distance;
                Vector2 correction = surface_normal * (penetration_length + 0.01f);
                a->position = Vector2Add(correction,a->position);

                float dot_impulse = Vector2DotProduct(a->velocity,surface_normal);

                Vector2 impulse;

                impulse.x = a->velocity.x - (2*dot_impulse*surface_normal.x);
                impulse.y = a->velocity.y - (2*dot_impulse*surface_normal.y);

                a->velocity = impulse * 0.55f;


                if(Vector2Length(a->velocity) < 0.01f){
                    a->velocity = Vector2{0.0f,0.0f};
                }
            }
        }
    }
}

void map_out(std::vector<Ball*>& entities){
    for(size_t i = 0;i< entities.size();){
        Ball *a = entities[i];
        if(a->position.y > Window_Height || a->position.y < 0 || a->position.x > Window_Width || a->position.x < 0 ){
            delete a;
            entities.erase(entities.begin()+i);
        }else{
            i++;
        }
    }
}

void physic(std::vector<Ball*> &entity,float &deltatime){
    for(size_t i = 0;i < entity.size();i++){
        OnGravity(*entity[i],deltatime);
    }
    map_out(entity);
    collision_detect(entity,deltatime);
    for(size_t i = 0;i < entity.size();i++){
    entity[i]->position = entity[i]->position + entity[i]->velocity;
    }
    
}