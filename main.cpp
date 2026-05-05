#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include "Object2D.h"
#include "ObjectPrimitives.h"

int main(int argc, char **argv) {
    // Define window dimensions
    const int window_width = 800;
    const int window_height = 450;

    // Create window
    InitWindow(window_width,window_height,"Raylib Example");
    SetTargetFPS(60);

    // Create scene
    Box* mouse = new Box();
    mouse->setPosition({0.0f,0.0f});
    mouse->setRotation(0.0f);
    mouse->setScale({1.0f,1.0f});
    mouse->size = {100.0f,100.0f};
    mouse->color = RED;
    mouse->reparent(nullptr);

    Box* point = new Box();
    point->setPosition({40.0f,40.0f});
    point->setRotation(0.0f);
    point->setScale({1.0f,1.0f});
    point->size = {10.0f,10.0f};
    point->color = BLUE;
    point->reparent(mouse);

    // Main loop
    while(!WindowShouldClose()) {
        mouse->setPosition(GetMousePosition());
        mouse->rotate(1.0f);

        float s = 0.5f * sin(GetTime()) + 0.5f;
        mouse->setScale({s,s});

        BeginDrawing();
        ClearBackground(DARKGRAY);
        mouse->_draw();
        EndDrawing();
    }

    // Destroy window
    CloseWindow();

    return 0;
}
