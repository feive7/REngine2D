#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include "engine/Object2D.h"
#include "engine/ObjectPrimitives.h"
#include "engine/Sprite2D.h"
#include "engine/Animation.h"

class Coconut : public Sprite2D {
public:
    Coconut() {
        setTexture("../../../../assets/sprites/coconut.png");
    }
    void _update() override {
        this->rotate(1);
    }
};

int main(int argc, char **argv) {
    // Define window dimensions
    const int window_width = 800;
    const int window_height = 450;

    // Create window
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(window_width,window_height,"Raylib Example");
    SetTargetFPS(60);

    // Create scene
    Object2D* scene = new Object2D();
    scene->setPosition({ 400.0f,225.0f });
    scene->setRotation(0.0f);
    scene->setScale({ 1.0f,1.0f });

    Coconut* coconut = new Coconut();
    coconut->setPosition({100.0f,10.0f });
    coconut->setRotation(0.0f);
    coconut->setScale({1.0f,1.0f});
    coconut->size = {200.0f,200.0f};
    coconut->reparent(scene);

    scene->readyTree();

    // Main loop
    while(!WindowShouldClose()) {
        scene->updateTree();
        BeginDrawing();
        ClearBackground(DARKGRAY);
        scene->drawTree();
        EndDrawing();
    }

    // Destroy window
    CloseWindow();

    return 0;
}
