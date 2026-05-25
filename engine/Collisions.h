#pragma once

enum CollisionShapeType : int {
	None,
	Box,
	Circle
};

class CollisionShape : public Object2D {
protected:
	CollisionShapeType shape = CollisionShapeType::None;
public:
	virtual bool contains(Vector2 point) = 0;
	virtual bool overlapping(CollisionShape* other) = 0;
	inline CollisionShapeType getShape() { return shape; }
};

class CollisionBox : public CollisionShape {
public:
	Vector2 size;
	CollisionBox() {
		this->shape = CollisionShapeType::Box;
	}
	bool contains(Vector2 point) override {
		// Localize point
		point -= getGlobalPosition();
		point = Vector2Rotate(point, getGlobalRotation() * DEG2RAD);

		Vector2 gscl = getGlobalScale() * size;
		return point.x > -gscl.x && point.x < gscl.x && point.y > -gscl.y && point.y < gscl.y;
	}
	bool overlapping(CollisionShape* other) override;
};

class CollisionCircle : public CollisionShape {
public:
	float radius;
	CollisionCircle() {
		this->shape = CollisionShapeType::Circle;
	}
	bool contains(Vector2 point) override {
		// Localize point
		point -= getGlobalPosition();

		float grad = getGlobalScale().x * radius;
		return hypot(point.x, point.y) < grad;
	}
	bool overlapping(CollisionShape* other) override;
};

bool TestAxis(Vector2 axis, std::vector<Vector2> verts_a, std::vector<Vector2> verts_b) {
	float min_od_a = FLT_MAX;
	float max_od_a = -FLT_MAX;
	for (const Vector2& vert : verts_a) {
		float od = Vector2DotProduct(vert, axis);
		min_od_a = fmin(min_od_a, od);
		max_od_a = fmax(max_od_a, od);
	}

	float min_od_b = FLT_MAX;
	float max_od_b = -FLT_MAX;
	for (const Vector2& vert : verts_b) {
		float od = Vector2DotProduct(vert, axis);
		min_od_b = fmin(min_od_b, od);
		max_od_b = fmax(max_od_b, od);
	}

	return !(max_od_a < min_od_b || max_od_b < min_od_a);
}

bool CollisionBox::overlapping(CollisionShape* other) {
	Vector2 this_gpos = getGlobalPosition();
	float this_grot = getGlobalRotation();
	Vector2 this_gscl = getGlobalScale() * size;
	CollisionShapeType other_shape = other->getShape();
	if (other_shape == CollisionShapeType::Box) {
		CollisionBox* other_box = dynamic_cast<CollisionBox*>(other);
		Vector2 other_gpos = other_box->getGlobalPosition();
		float other_grot = other_box->getGlobalRotation();
		Vector2 other_gscl = other_box->getGlobalScale() * other_box->size;


		Vector2 box_a_normal = { cos(this_grot * -DEG2RAD),sin(this_grot * -DEG2RAD) };
		Vector2 box_b_normal = { cos(other_grot * -DEG2RAD),sin(other_grot * -DEG2RAD) };

		Vector2 box_a_1 = Vector2Rotate(this_gscl, this_grot * -DEG2RAD) + this_gpos;
		Vector2 box_a_2 = Vector2Rotate(this_gscl * Vector2{ -1,1 }, this_grot * -DEG2RAD) + this_gpos;
		Vector2 box_a_3 = Vector2Rotate(this_gscl * Vector2{ -1,-1 }, this_grot * -DEG2RAD) + this_gpos;
		Vector2 box_a_4 = Vector2Rotate(this_gscl * Vector2{ 1,-1 }, this_grot * -DEG2RAD) + this_gpos;

		Vector2 box_b_1 = Vector2Rotate(other_gscl, other_grot * -DEG2RAD) + other_gpos;
		Vector2 box_b_2 = Vector2Rotate(other_gscl * Vector2{ -1,1 }, other_grot * -DEG2RAD) + other_gpos;
		Vector2 box_b_3 = Vector2Rotate(other_gscl * Vector2{ -1,-1 }, other_grot * -DEG2RAD) + other_gpos;
		Vector2 box_b_4 = Vector2Rotate(other_gscl * Vector2{ 1,-1 }, other_grot * -DEG2RAD) + other_gpos;

		Vector2 axis_1 = box_a_normal;
		Vector2 axis_2 = box_b_normal;
		Vector2 axis_3 = Vector2{ -box_a_normal.y,box_a_normal.x };
		Vector2 axis_4 = Vector2{ -box_b_normal.y,box_b_normal.x };

		if (!TestAxis(axis_1, { box_a_1,box_a_2,box_a_3,box_a_4 }, { box_b_1,box_b_2,box_b_3,box_b_4 })) return false;
		if (!TestAxis(axis_2, { box_a_1,box_a_2,box_a_3,box_a_4 }, { box_b_1,box_b_2,box_b_3,box_b_4 })) return false;
		if (!TestAxis(axis_3, { box_a_1,box_a_2,box_a_3,box_a_4 }, { box_b_1,box_b_2,box_b_3,box_b_4 })) return false;
		if (!TestAxis(axis_4, { box_a_1,box_a_2,box_a_3,box_a_4 }, { box_b_1,box_b_2,box_b_3,box_b_4 })) return false;

		return true;
	}
	else if (other_shape == CollisionShapeType::Circle) {
		CollisionCircle* other_circle = dynamic_cast<CollisionCircle*>(other);
		Vector2 other_gpos = Vector2Rotate(other_circle->getGlobalPosition() - this_gpos, this_grot * DEG2RAD);
		float other_grad = other_circle->getGlobalScale().x * other_circle->radius;

		// SDF method
		Vector2 d = Vector2{ abs(other_gpos.x),abs(other_gpos.y) } - this_gscl;
		return Vector2Length(Vector2{ fmax(d.x,0.0f),fmax(d.y,0.0f) }) + fmin(fmax(d.x, d.y), 0.0f) < other_grad;
	}
	return false;
}

bool CollisionCircle::overlapping(CollisionShape* other) {
	Vector2 this_gpos = getGlobalPosition();
	float this_grad = getGlobalScale().x * radius;
	CollisionShapeType other_shape = other->getShape();
	if (other_shape == CollisionShapeType::Box) {
		return other->overlapping(this);
	}
	else if (other->getShape() == CollisionShapeType::Circle) {
		CollisionCircle* other_circle = dynamic_cast<CollisionCircle*>(other);
		Vector2 other_gpos = other_circle->getGlobalPosition();
		float other_grad = other_circle->getGlobalScale().x * other_circle->radius;
		return Vector2DistanceSqr(this_gpos, other_gpos) < this_grad * this_grad + other_grad * other_grad;
	}
	return false;
}