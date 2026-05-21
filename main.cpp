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
    InitEngine(window_width, window_height, "Raylib Example");
    SetTargetFPS(60);

    // Create scene
    Sprite2D* sprite = new Sprite2D();
    sprite->setPosition({400.0f,225.0f});
    sprite->size = {100.0f,100.0f};
    sprite->setTexture("../assets/funi.jpg");
    sprite->reparent(scene);

    // Initialize scene tree
    ReadyTree();

    // Main loop
    while(!WindowShouldClose()) {
        UpdateTree(); // Run _update() for every element in tree

        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawTree();
        DrawFPS(5, 5);
        EndDrawing();
    }

    // Clean up
    Quit();


    return 0;
}
