#pragma once
#include <box2d/box2d.h>
#define R2B(v) b2Vec2{v.x,v.y}
#define B2R(v) Vector2{v.x,v.y}

class PhysLayer;

class PhysBody : public Object2D {
    bool initialized = false;
public:
    b2BodyDef body_def = b2DefaultBodyDef();
    b2BodyId body_id = b2_nullBodyId;

    PhysLayer* parent_phys_layer;

    virtual void create() = 0; // Shape creation function
    void initializeBody(); // Initializes body into parent_phys_layer

    void _update() override;


    void setFixed(bool fixed) {
        b2BodyType type = (fixed ? b2_staticBody : b2_dynamicBody);
        if(initialized) b2Body_SetType(body_id,type);
        else body_def.type = type;
    }
};

class PhysLayer : public Object {
    bool initialized = false;
    float physics_scale = 1.0f;
public:
    b2WorldDef world_def = b2DefaultWorldDef();
    b2WorldId world_id = b2_nullWorldId;

    std::vector<PhysBody*> bodies;

    void setPhysicsScale(float scale) {
        if(!initialized) this->physics_scale = scale;
    }
    inline float getPhysicsScale() {
        return physics_scale;
    }

    void add(PhysBody* body) {
        bodies.push_back(body);
        body->parent_phys_layer = this;
    }
    void _update() override {
        const float timestep = 1.0f / 60.0f;
        const int substep_count = 4;
        b2World_Step(world_id,timestep,substep_count);
    }
    void _ready() override {
        world_id = b2CreateWorld(&world_def);
        for(PhysBody* body : bodies) {
            if(!body->parent) continue;
            body->initializeBody();
            body->create();
        }
        initialized = true;
    }
    void setGravity(Vector2 new_gravity) {
        if(initialized) b2World_SetGravity(world_id,R2B(new_gravity));
        else world_def.gravity = R2B(new_gravity);
    }
};

void PhysBody::_update() {
    float physics_scale = parent_phys_layer->getPhysicsScale();
    b2Vec2 pos = b2Body_GetPosition(body_id);
    this->setPosition(pos.x/physics_scale,pos.y/physics_scale);
    b2Rot rot = b2Body_GetRotation(body_id);
    this->setRotation(b2Rot_GetAngle(rot)*-RAD2DEG);
}

void PhysBody::initializeBody() {
    float physics_scale = parent_phys_layer->getPhysicsScale();
    position /= physics_scale;
    body_def.position = R2B(position);
    body_def.rotation = b2MakeRot(rotation);
    body_id = b2CreateBody(parent_phys_layer->world_id,&body_def);
    initialized = true;
}

class PhysBox : public PhysBody {
public:
    Vector2 size;
    void create() override {
        Vector2 gscl = getGlobalScale() * size * parent_phys_layer->getPhysicsScale();
        b2Polygon box = b2MakeBox(gscl.x,gscl.y);
        b2ShapeDef shape_def = b2DefaultShapeDef();
        shape_def.density = 1.0f;
        shape_def.material.friction = 0.3f;
        b2CreatePolygonShape(body_id,&shape_def,&box);
    }
};
