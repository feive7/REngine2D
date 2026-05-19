#pragma once
#include "Object.h"
#include "Object2D.h"
#include "Shapes.h"
#include "SolidShapes.h"
#include "Sprite2D.h"
#include "Animation.h"

struct {
	Vector2 getPosition() {
		return GetMousePosition();
	}
	Vector2 getDelta() {
		return GetMouseDelta();
	}
} Mouse;

// Root object
Object* scene;
std::vector<VisualObject*> drawables;

VisualObject::VisualObject() {
	drawables.push_back(this);
}

void InitEngine() {
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

void DeleteEverything() {
	Remove(scene);
}
