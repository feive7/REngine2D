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
    SetTargetFPS(120);
    InitEngine();

    // Create scene
    RectShape* rect = new RectShape();
    rect->position = { 400.0f,225.0f };
    rect->rotation = 0.0f;
    rect->scale = { 1.0f,1.0f };
    rect->size = { 100.0f,75.0f };
    rect->reparent(scene);

    // Initialize scene tree
    ReadyTree();

    // Main loop
    while(!WindowShouldClose()) {
        UpdateTree(); // Run _update() for every element in tree
        rect->rotate(1.0f);

        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawTree();
        DrawFPS(5, 5);
        EndDrawing();
    }

    // Destroy window
    CloseWindow();

    return 0;
}
