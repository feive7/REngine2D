#pragma once

class CollisionBox : public BoxShape {
public:
    bool enabled = true;
    bool collidingWith(CollisionBox* other) {
        Rectangle this_rect = this->getRectangle();
        Rectangle other_rect = other->getRectangle();
        return
            this_rect.x < other_rect.x + other_rect.width &&
            this_rect.x + this_rect.width > other_rect.x &&
            this_rect.y < other_rect.y + other_rect.height &&
            this_rect.y + this_rect.height > other_rect.y;
    }
    bool contains(CollisionBox* other) {
        Rectangle this_rect = this->getRectangle();
        Rectangle other_rect = other->getRectangle();
        return
            this_rect.x < other_rect.x &&
            this_rect.x + this_rect.width > other_rect.x + other_rect.width &&
            this_rect.y < other_rect.y &&
            this_rect.y + this_rect.height > other_rect.y + other_rect.height;
    }
};
