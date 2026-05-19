#pragma once
class Object2D : public Object {
public:
    Vector2 position = Vector2Zero();
    float rotation = 0.0f;
    Vector2 scale = Vector2One();

    Matrix transform = MatrixIdentity();

    Object2D* getParent2D() { return dynamic_cast<Object2D*>(parent); }

    Vector2 getPosition() { return position; }
    float getRotation() { return rotation; }
    Vector2 getScale() { return scale; }

    void setPosition(Vector2 new_position) { this->position = new_position; }
    void setPosition(float x, float y) { this->position = {x,y}; }
    void setX(float x) { this->position.x = x; }
    void setY(float y) { this->position.y = y; }
    void setRotation(float new_rotation) { this->rotation = new_rotation; }
    void setScale(Vector2 new_scale) { this->scale = new_scale; }

    void move(Vector2 amount) { this->position += amount; }
    void moveX(float amount) { this->position.x += amount; }
    void moveY(float amount) { this->position.y += amount; }
    void rotate(float amount) { this->rotation += amount; }

    Matrix getLocalTransform() {
        Matrix local_transform = MatrixIdentity();
        local_transform *= MatrixRotateZ(rotation * -DEG2RAD);
        local_transform *= MatrixTranslate(position.x,position.y,0.0f);
        return local_transform;
    }
    Matrix getGlobalTransform() {
        Matrix parent_matrix = MatrixIdentity();
        if(Object2D* parent2D = getParent2D()) parent_matrix = parent2D->getGlobalTransform();
        return getLocalTransform() * parent_matrix;
    }

    Vector2 getGlobalPosition() {
        if(Object2D* parent2D = getParent2D())
            return Vector2Rotate(parent2D->scale * position, parent2D->rotation * -DEG2RAD) + parent2D->getGlobalPosition();
        return position;
    }
    float getGlobalRotation() {
        if(Object2D* parent2D = getParent2D())
            return rotation + parent2D->getGlobalRotation();
        return rotation;
    }
    Vector2 getGlobalScale() {
        if(Object2D* parent2D = getParent2D())
            return scale * parent2D->getGlobalScale();
        return scale;
    }
};


