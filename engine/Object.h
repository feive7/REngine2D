#pragma once
#include <vector>
#include <algorithm>
class Object {
public:
    Object* parent = nullptr;
    std::vector<Object*> children = {};

    virtual ~Object() {}
    virtual void _draw() {}
    virtual void _update() {}
    virtual void _ready() {}

    void drawTree() {
        _draw();
        for (Object* child : children) {
            child->drawTree();
        }
    }
    void updateTree() {
        _update();
        for (Object* child : children) {
            child->updateTree();
        }
    }
    void readyTree() {
        _ready();
        for (Object* child : children) {
            child->readyTree();
        }
    }

    Object* addChild(Object* new_child) {
        new_child->reparent(this);
        return new_child;
    }
    Object& addChild(Object& new_child) {
        new_child.reparent(this);
        return new_child;
    }
    void reparent(Object* new_parent) {
        if (parent == new_parent)
            return;

        if (new_parent) {
            auto child = std::find(new_parent->children.begin(), new_parent->children.end(), this);
            if (child != new_parent->children.end())
                new_parent->children.erase(child);
        }

        parent = new_parent;
        if (parent)
            parent->children.push_back(this);
    }
    void detach() {
        if (!parent)
            return;
        reparent(nullptr);
    }
};
