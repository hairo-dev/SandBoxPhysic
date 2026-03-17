#include "config.h"
#include "Entity.h"
#include "physic.h"

std::vector<Ball*> Entity;

void create_ball(Vector2 position,Vector2 velocity,float radius,Color color,BodyType type){
    Ball *Entity_temp = new Ball(position,velocity,radius,color,type);

    Entity.push_back(Entity_temp);
}

int main(){
    
    InitWindow(Window_Width,Window_Height,"trigon");
    SetTargetFPS(60);

    create_ball(Vector2{Window_Width/2,Window_Height/2+150},Vector2{0.0f,0.0f},80,BLUE,BodyType::BODY_STATIC);

    create_ball(Vector2{Window_Width/2-225,Window_Height/2+250},Vector2{0.0f,0.0f},80,BLUE,BodyType::BODY_STATIC);

    create_ball(Vector2{Window_Width/2+225,Window_Height/2+250},Vector2{0.0f,0.0f},80,BLUE,BodyType::BODY_STATIC);

    while (!WindowShouldClose())
    {
        float deltatime = GetFrameTime();
        physic(Entity,deltatime);

        create_ball(Vector2{Window_Width/2,Window_Height/2-200},Vector2{1.0f,0.0f},10,GREEN,BodyType::BODY_DYNAMIC);
        create_ball(Vector2{Window_Width/2,Window_Height/2-200},Vector2{-1.0f,0.0f},10,RED,BodyType::BODY_DYNAMIC);

        BeginDrawing();
        ClearBackground(BLACK);
        //render
        for(size_t i = 0;i < Entity.size();i++){
            DrawCircle(Entity[i]->position.x,Entity[i]->position.y,Entity[i]->radius,Entity[i]->color);
        }

        EndDrawing();
    }
    for (auto p : Entity)
    delete p;
    Entity.clear();
    
    CloseWindow();
    return 0;
}