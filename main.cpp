#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include "engine/Engine.h"
void DrawPoint(Vector2 p, Color color = BLACK) {
	DrawCircleV(p, 3.0f, color);
}
void DebugLine(const char* text, bool reset = false) {
	static int y = 5;
	if (reset) {
		y = 5;
		return;
	}
	DrawText(text, 5, y, 20, WHITE);
	y += 20;
}
void DebugLine(Vector2 v) { DebugLine(TextFormat("%f %f", v.x, v.y)); }
void DebugLine(float v) { DebugLine(TextFormat("%f", v)); }

int main(int argc, char** argv) {
	// Define window dimensions
	const int window_width = 1600;
	const int window_height = 900;

	// Create window
	InitEngine(window_width, window_height, "Raylib Example");
	SetTargetFPS(60);

	// Create scene
	Sprite2D* ethan = new Sprite2D();
	ethan->size = { 100,100 };
	ethan->setPosition(800, 450);
	ethan->setTexture("../../../assets/ethan.jpg");
	ethan->reparent(scene);

	CollisionBox* ethan_collision = new CollisionBox();
	ethan_collision->size = ethan->size;
	ethan_collision->reparent(ethan);

	SolidCircle* roland = new SolidCircle();
	roland->radius = 40.0f;
	roland->setPosition(800, 450);
	roland->reparent(scene);
	
	CollisionCircle* roland_collision = new CollisionCircle();
	roland_collision->radius = roland->radius;
	roland_collision->reparent(roland);

	// Initialize scene tree
	ReadyTree();

	// Main loop
	while (!WindowShouldClose()) {
		UpdateTree(); // Run _update() for every element in tree
		ethan->rotate(1);
		roland->setPosition(Mouse.getPosition());
		roland->rotate(Mouse.getWheel() * 10);

		BeginDrawing();
		ClearBackground(DARKGRAY);
		DrawTree();
		DebugLine("", true);
		if (roland_collision->overlapping(ethan_collision)) {
			DebugLine("Overlap");
		}
		//DrawFPS(5, 5);
		EndDrawing();
	}

	// Clean up
	Quit();


	return 0;
}
