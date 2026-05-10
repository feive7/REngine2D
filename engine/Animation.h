#pragma once
struct Keyframe {
    float timestamp;
    Vector2 position;
    float rotation;
    Vector2 scale;
};
class Animation : public Object2D {
    int frame = 0;
    int next_frame = 1;
    float time = 0;
public:
    std::vector<Keyframe> keyframes;
    bool playing = false;
    bool looping = true;
    Animation() {
        keyframes.push_back({});
    }
    void _ready() override {
        // Starting frame
        keyframes[0] = {
            0.0f,
            position,
            rotation,
            scale,
        };
    }
    void setTime(float time) {
        this->time = 0;
    }
    void getTransformNow() {
        Keyframe last_keyframe = keyframes[frame];
        float last_timestamp = last_keyframe.timestamp;
        Vector2 last_position = last_keyframe.position;
        float last_rotation = last_keyframe.rotation;
        Vector2 last_scale = last_keyframe.scale;

        Keyframe next_keyframe = keyframes[next_frame];
        float next_timestamp = next_keyframe.timestamp;
        Vector2 next_position = next_keyframe.position;
        float next_rotation = next_keyframe.rotation;
        Vector2 next_scale = next_keyframe.scale;

        float p = getFrameProgress();
        //p = 3 * p * p - 2 * p * p * p;
        this->position = Vector2Lerp(last_position, next_position, p);
        this->rotation = Lerp(last_rotation, next_rotation, p);
        this->scale = Vector2Lerp(last_scale, next_scale, p);
    }
    float getFrameProgress() {
        return time - keyframes[frame].timestamp;
    }
    int getFrame() {
        return frame;
    }
    void nextFrame() {
        frame = next_frame;

        // Reset time if looped
        if (looping && frame == 0) {
            time = 0;
        }
        
        next_frame++;
        if (next_frame == keyframes.size()) {
            if (looping) {
                next_frame = 0;
            }
            else {
                playing = false;
            }
        }
    }
    void _update() override {
        if (!playing) return;
        this->time += GetFrameTime();
        getTransformNow();
        if (getFrameProgress() >= 1) {
            nextFrame();
        }
    }
    void _draw() override {
        for (int i = 0; i < keyframes.size() - !looping; i++) {
            DrawLineV(keyframes[i].position, keyframes[(i + 1)%keyframes.size()].position, RED);
        }
        drawChildren();
    }
};
