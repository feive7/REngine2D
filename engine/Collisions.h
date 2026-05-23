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
        point = Vector2Rotate(point,getGlobalRotation()*DEG2RAD);

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
        return hypot(point.x,point.y) < grad;
    }
    bool overlapping(CollisionShape* other) override;
};

bool CollisionBox::overlapping(CollisionShape* other) {
    CollisionBox* other_box = dynamic_cast<CollisionBox*>(other);
    Vector2 v11 = Vector2Rotate();
    return false;
}

bool CollisionCircle::overlapping(CollisionShape* other) {
    return false;
}
