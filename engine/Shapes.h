#pragma once
class Shape : public Object2D {
public:
	virtual bool pointInside(Vector2) = 0;
};

class RectShape : public Shape {
public:
	Vector2 size;
	bool pointInside(Vector2 point) override {
		Vector2 center = getGlobalPosition();
		return 
			center.x - size.x < point.x &&
			center.x + size.x > point.x &&
			center.y - size.y < point.y &&
			center.y + size.y > point.y;
	}
	void _draw() override {
		Vector2 center = getGlobalPosition();
		float grot = getGlobalRotation();
		Vector2 gscl = getGlobalScale() * size;
		Rectangle rect = {
			center.x,
			center.y,
			gscl.x * 2,
			gscl.y * 2
		};
		DrawRectanglePro(rect,{gscl.x,gscl.y}, grot, BLUE);
	}
};

class CircleShape : public Shape {
public:
	float radius;
	bool pointInside(Vector2 point) override {
		Vector2 center = getGlobalPosition();
		return hypot(point.x - center.x, point.y - center.y) < radius * fmax(scale.x, scale.y);
	}
	void _draw() override {
		Vector2 center = getGlobalPosition();
		float grot = getGlobalRotation();
		float gscl = getGlobalScale().x * radius;
		DrawCircleV(center,gscl,BLUE);
	}
};
