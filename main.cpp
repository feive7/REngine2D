#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include "engine/Object2D.h"
#include "engine/ObjectPrimitives.h"
#include "engine/Sprite2D.h"

int main(int argc, char **argv) {
    // Define window dimensions
    const int window_width = 800;
    const int window_height = 450;

    // Create window
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(window_width,window_height,"Raylib Example");
    SetTargetFPS(60);

    // Create scene
    Sprite2D* mouse = new Sprite2D("../assets/sprites/coconut.png");
    mouse->setPosition({400.0f,225.0f});
    mouse->setRotation(0.0f);
    mouse->setScale({1.0f,1.0f});
    mouse->size = {100.0f,100.0f};
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
        BeginDrawing();
        ClearBackground(DARKGRAY);
        mouse->_draw();
        EndDrawing();
    }

    // Destroy window
    CloseWindow();

    return 0;
}
