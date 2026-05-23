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
    SolidBox* box = new SolidBox();
    box->size = {50.0f,50.0f};
    box->setPosition(400.0f,225.0f);
    box->reparent(scene);

    CollisionBox* collision = new CollisionBox();
    collision->size = box->size;
    collision->reparent(box);

    // Initialize scene tree
    ReadyTree();

    // Main loop
    while(!WindowShouldClose()) {
        UpdateTree(); // Run _update() for every element in tree

        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawTree();
        DrawCircleV(collision->closestPoint(Mouse.getPosition()),3.0f,BLUE);
        DrawFPS(5, 5);
        EndDrawing();
    }

    // Clean up
    Quit();


    return 0;
}
