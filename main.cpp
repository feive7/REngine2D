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
    PhysLayer* physlayer = new PhysLayer();
    physlayer->setPhysicsScale(0.05f);
    physlayer->setGravity({0.0f,9.0f});
    physlayer->reparent(scene);

    PhysBox* box = new PhysBox();
    box->setPosition(530.0f,200.0f);
    box->size = {70.0f,70.0f};
    box->reparent(scene);
    box->setFixed(false);
    physlayer->add(box);

    PhysBox* ground = new PhysBox();
    ground->setPosition(400.0f,300.0f);
    ground->size = {100.0f,5.0f};
    ground->reparent(scene);
    ground->setFixed(true);
    physlayer->add(ground);

    Sprite2D* sprite = new Sprite2D("../assets/funi.jpg");
    sprite->size = box->size;
    sprite->reparent(box);

    SolidBox* ground_sprite = new SolidBox();
    ground_sprite->size = ground->size;
    ground_sprite->reparent(ground);

    // Initialize scene tree
    ReadyTree();

    // Main loop
    while(!WindowShouldClose()) {
        UpdateTree(); // Run _update() for every element in tree

        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawTree();
        DrawFPS(5, 5);
        DrawText(TextFormat("Sprite Pos: %f %f",box->position.x,box->position.y),5,25,20,WHITE);
        EndDrawing();
    }

    // Clean up
    Quit();


    return 0;
}
