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
};

class CircleShape : public Shape {
public:
	float radius;
	bool pointInside(Vector2 point) override {
		Vector2 center = getGlobalPosition();
		return hypot(point.x - center.x, point.y - center.y) < radius * fmax(scale.x, scale.y);
	}
};
