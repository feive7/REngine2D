#pragma once
class SolidCircle : public CircleShape, public VisualObject {
public:
    void _draw() override {
        Vector2 gpos = getGlobalPosition();
        DrawCircleV(gpos,radius,color);
    }
};

class SolidRect : public RectShape, public VisualObject {
    void _draw() override {
        Vector2 gpos = getGlobalPosition();
        float grot = getGlobalRotation();
        Vector2 gscl = getGlobalScale() * size;

        Rectangle rect = {gpos.x,gpos.y,gscl.x * 2,gscl.y * 2};
        DrawRectanglePro(rect,gscl,-grot,WHITE);
    }
};
