#pragma once
class Shape : public Object2D {
public:
	virtual bool pointInside(Vector2) = 0;
};

class BoxShape : public Shape {
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
	Rectangle getRectangle() {
		Vector2 gpos = getGlobalPosition();
		Vector2 gscl = getGlobalScale() * size;
		return {
			gpos.x - gscl.x,
			gpos.y - gscl.y,
			gscl.x * 2,
			gscl.y * 2
		};
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
