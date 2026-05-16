#pragma once
#include "Object.h"
#include "Object2D.h"
#include "ObjectPrimitives.h"
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

void InitEngine() {
	scene = new Object();
}

void ReadyTree() {
	scene->updateTree();
}
void UpdateTree() {
	scene->updateTree();
}
void DrawTree() {
	scene->drawTree();
}

