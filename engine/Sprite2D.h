#pragma once
class Sprite2D : public Object2D {
public:
    Vector2 size;
    Texture texture;
    Sprite2D(const char* filename, bool gen_mipmaps = true) {
        this->texture = LoadTexture(filename);
        this->size = {(float)texture.width,(float)texture.height};
        if(gen_mipmaps) GenTextureMipmaps(&texture);
    }
    Sprite2D(Texture texture, bool gen_mipmaps = true) {
        this->texture = texture;
        this->size = {(float)texture.width,(float)texture.height};
        if(gen_mipmaps) GenTextureMipmaps(&texture);
    }
    void _draw() override {
        Rectangle src_rect = {0.0f,0.0f,(float)texture.width,(float)texture.height};

        Vector2 gpos = getGlobalPosition();
        float grot = getGlobalRotation();
        Vector2 gscl = getGlobalScale();
        Rectangle dst_rect = {gpos.x,gpos.y,gscl.x * size.x,gscl.y * size.y};
        DrawTexturePro(texture,src_rect,dst_rect,gscl*size*0.5f,-grot,WHITE);
        drawChildren();
    }
    void _update() override {

    };
};
