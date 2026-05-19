#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include "engine/Engine.h"

int main(int argc, char** argv) {
    // Define window dimensions
    const int window_width = 800;
    const int window_height = 450;

    // Create window
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(window_width, window_height, "Raylib Example");
    SetTargetFPS(60);
    InitEngine();

    // Create scene
    Sprite2D* sprite = new Sprite2D("../assets/funi.jpg");
    sprite->setPosition(400.0f,225.0f);
    sprite->size = {100.0f,100.0f};
    sprite->reparent(scene);
    CollisionBox* sprite_collision = new CollisionBox();
    sprite_collision->size = sprite->size;
    sprite_collision->reparent(sprite);

    SolidBox* mouse = new SolidBox();
    mouse->size = {20.0f,20.0f};
    mouse->color = BLUE;
    mouse->reparent(scene);
    CollisionBox* mouse_collision = new CollisionBox();
    mouse_collision->size = mouse->size;
    mouse_collision->reparent(mouse);

    // Initialize scene tree
    ReadyTree();

    // Main loop
    while(!WindowShouldClose()) {
        UpdateTree(); // Run _update() for every element in tree
        mouse->setPosition(Mouse.getPosition());


        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawTree();
        if(mouse_collision->collidingWith(sprite_collision)) {
            DrawText("Colliding!",5,25,20,WHITE);
        }
        DrawFPS(5, 5);
        EndDrawing();
    }

    // Clean up
    DeleteEverything();

    // Destroy window
    CloseWindow();

    return 0;
}
