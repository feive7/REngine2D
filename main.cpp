#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include "engine/Object2D.h"
#include "engine/ObjectPrimitives.h"
#include "engine/Sprite2D.h"
#include "engine/Animation.h"

int main(int argc, char **argv) {
    // Define window dimensions
    const int window_width = 800;
    const int window_height = 450;

    // Create window
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(window_width,window_height,"Raylib Example");
    SetTargetFPS(60);

    // Create scene
    Box* point = new Box();
    point->setPosition({0.0f,10.0f });
    point->setRotation(0.0f);
    point->setScale({1.0f,1.0f});
    point->size = {10.0f,20.0f};
    point->color = BLUE;

    Animation* anim = new Animation();
    anim->setPosition({400.0f,225.0f});
    anim->keyframes.push_back(Keyframe{
        1.0f,
        {350.0f,225.0f},
        180.0f,
        {1.0f,1.0f},
    });
    anim->keyframes.push_back(Keyframe{
        2.0f,
        {400.0f,100.0f},
        90.0f,
        {1.0f,1.0f},
        });
    anim->keyframes.push_back(Keyframe{
        3.0f,
        {450.0f,225.0f},
        270.0f,
        {4.0f,4.0f},
    });
    anim->playing = true;
    anim->looping = true;
    anim->_ready();
    point->reparent(anim);

    // Main loop
    while(!WindowShouldClose()) {
        anim->_update();
        BeginDrawing();
        ClearBackground(DARKGRAY);
        anim->_draw();
        EndDrawing();
    }

    // Destroy window
    CloseWindow();

    return 0;
}
