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
    sprite->size = {100.0f,100.0f};
    sprite->reparent(scene);

    // Initialize scene tree
    ReadyTree();

    // Main loop
    while(!WindowShouldClose()) {
        UpdateTree(); // Run _update() for every element in tree
        Vector2 to_mouse = Vector2Normalize(Mouse.getPosition() - sprite->position);
        sprite->move(to_mouse);

        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawTree();
        DrawFPS(5, 5);
        EndDrawing();
    }

    // Clean up
    DeleteEverything();

    // Destroy window
    CloseWindow();

    return 0;
}
