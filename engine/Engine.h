#pragma once
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
Object2D* scene;

void InitEngine() {
	scene = new Object2D();
	scene->setPosition({ 0.0f,0.0f });
	scene->setRotation(0.0f);
	scene->setScale({ 1.0f,1.0f });
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

