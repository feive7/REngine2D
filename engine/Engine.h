#pragma once
#include "Object.h"
#include "Object2D.h"
#include "Shapes.h"
#include "SolidShapes.h"
#include "Sprite2D.h"
#include "Animation.h"
#include "Collisions.h"
#include "Physics.h"

struct {
	Vector2 getPosition() {
		return GetMousePosition();
	}
	Vector2 getDelta() {
		return GetMouseDelta();
	}
	float getMouseWheel() {
		return GetMouseWheelMove();
	}
} Mouse;

// Root object
Object* scene;
std::vector<VisualObject*> drawables;

VisualObject::VisualObject() {
	drawables.push_back(this);
}

void InitEngine(int window_width, int window_height, const char* window_title) {
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(window_width, window_height, "Raylib Example");
	scene = new Object();
}

void ReadyTree() {
	scene->readyTree();
}
void UpdateTree() {
	scene->updateTree();
}
void DrawTree() {
	for(int i = 0; i < drawables.size(); i++) {
		drawables[i]->_draw();
	}
}

void Quit() {
	// Delete game objects
	Remove(scene);

	// Destroy window
	CloseWindow();
}
