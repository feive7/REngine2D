#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include "engine/Engine.h"

int main(int argc, char **argv) {
    // Define window dimensions
    const int window_width = 800;
    const int window_height = 450;

    // Create window
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(window_width,window_height,"Raylib Example");
    SetTargetFPS(60);
    InitEngine();

    // Create scene
    Sprite2D* coconut = new Sprite2D("../../../../assets/sprites/coconut.png");
    coconut->setPosition({ 0.0f,0.0f });
    coconut->setRotation(0.0f);
    coconut->setScale({1.0f,1.0f});
    coconut->size = {200.0f,200.0f};
    coconut->reparent(scene);

    // Initialize scene tree
    ReadyTree();

    // Main loop
    while(!WindowShouldClose()) {
        coconut->setPosition(Mouse.getPosition());
        UpdateTree();
        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawTree();
        EndDrawing();
    }

    // Destroy window
    CloseWindow();

    return 0;
}
