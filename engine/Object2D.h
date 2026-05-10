#pragma once
#include <vector>
#include <algorithm>
class Object2D {
public:
    Vector2 position = Vector2Zero();
    float rotation = 0.0f;
    Vector2 scale = Vector2One();

    Matrix transform = MatrixIdentity();

    Object2D* parent = nullptr;
    std::vector<Object2D*> children = {};

    virtual ~Object2D() {}
    virtual void _draw() {}
    virtual void _update() {}
    virtual void _ready() {}

    void drawTree() {
        _draw();
        for(Object2D* child : children) {
            child->drawTree();
        }
    }
    void updateTree() {
        _update();
        for (Object2D* child : children) {
            child->updateTree();
        }
    }
    void readyTree() {
        _ready();
        for (Object2D* child : children) {
            child->readyTree();
        }
    }

    Object2D* addChild(Object2D* new_child) {
        new_child->reparent(this);
        return new_child;
    }
    void reparent(Object2D* new_parent) {
        if(parent == new_parent)
            return;

        if(new_parent) {
            auto child = std::find(new_parent->children.begin(), new_parent->children.end(), this);
            if(child != new_parent->children.end())
                new_parent->children.erase(child);
        }

        parent = new_parent;
        if(parent)
            parent->children.push_back(this);
    }
    void detach() {
        if(!parent)
            return;
        reparent(nullptr);
    }

    Vector2 getPosition() {
        return position;
    }
    float getRotation() {
        return rotation;
    }
    Vector2 getScale() {
        return scale;
    }

    void setPosition(Vector2 new_position) {
        this->position = new_position;
    }
    void setRotation(float new_rotation) {
        this->rotation = new_rotation;
    }
    void setScale(Vector2 new_scale) {
        this->scale = new_scale;
    }

    void move(Vector2 amount) {
        this->position += position;
    }
    void rotate(float amount) {
        this->rotation += amount;
    }

    void moveX(float amount) {
        this->position.x += amount;
    }
    void moveY(float amount) {
        this->position.y += amount;
    }

    Matrix getLocalTransform() {
        Matrix local_transform = MatrixIdentity();
        local_transform *= MatrixRotateZ(rotation);
        local_transform *= MatrixTranslate(position.x,position.y,0.0f);
        return local_transform;
    }
    Matrix getGlobalTransform() {
        Matrix parent_matrix = MatrixIdentity();
        if(parent)
            parent_matrix = parent->getGlobalTransform();
        return getLocalTransform() * parent_matrix;
    }

    Vector2 getGlobalPosition() {
        if(parent)
            return Vector2Rotate(parent->scale * position,parent->rotation * -DEG2RAD) + parent->getGlobalPosition();
        return position;
    }
    float getGlobalRotation() {
        if(parent)
            return rotation + parent->getGlobalRotation();
        return rotation;
    }
    Vector2 getGlobalScale() {
        if(parent)
            return scale * parent->getGlobalScale();
        return scale;
    }
};
