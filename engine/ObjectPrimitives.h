#pragma once
class Circle : public Object2D {
public:
    float radius;
    Color color;
    void _draw() override {
        DrawCircleV(getGlobalPosition(),radius,color);
    }
    void _update() override {

    }
};

class Box : public Object2D {
public:
    Vector2 size;
    Color color;
    void _draw() override {
        Vector2 gpos = getGlobalPosition();
        float grot = getGlobalRotation();
        Vector2 gscale = size * getGlobalScale();
        Rectangle rect = {gpos.x,gpos.y,gscale.x,gscale.y};
        DrawRectanglePro(rect,{rect.width/2.0f,rect.height/2.0f},-grot,color);
    }
};
