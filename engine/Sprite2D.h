#pragma once
#include "Shapes.h"
class Sprite2D : public RectShape, public VisualObject {
public:
    Texture texture;
    Sprite2D() {}
    Sprite2D(const char* filename, bool gen_mipmaps = true) {
        setTexture(filename, gen_mipmaps);
    }
    Sprite2D(Texture texture, bool gen_mipmaps = true) {
        setTexture(texture, gen_mipmaps);
    }
    void setTexture(const char* filename, bool gen_mipmaps = true) {
        this->texture = LoadTexture(filename);
        if (gen_mipmaps) GenTextureMipmaps(&texture);
    }
    void setTexture(Texture texture, bool gen_mipmaps = true) {
        this->texture = texture;
        if (gen_mipmaps) GenTextureMipmaps(&texture);
    }
    void _draw() override {
        Rectangle src_rect = {0.0f,0.0f,(float)texture.width,(float)texture.height};

        Vector2 gpos = getGlobalPosition();
        float grot = getGlobalRotation();
        Vector2 gscl = getGlobalScale();
        Rectangle dst_rect = {gpos.x,gpos.y,gscl.x * size.x,gscl.y * size.y};
        DrawTexturePro(texture,src_rect,dst_rect,gscl*size*0.5f,-grot,WHITE);
    }
    void _update() override {

    };
};
