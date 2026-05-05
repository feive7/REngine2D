#pragma once
struct Transform2D {
    Vector2 translation;
    float rotation;
    Vector2 scale;
};

Transform2D CombineTransform(Transform2D a, Transform2D b) {
    Transform2D result;
    result.translation = a.translation + b.translation;
    result.rotation = a.rotation + b.rotation;
    result.scale = a.scale * b.scale;
    return result;
}
Vector2 TransformVector2(Vector2 v, Transform2D transform) {
    Vector2 result = v;
    result = Vector2Rotate(result,transform.rotation);
    result += transform.translation;
    result *= transform.scale;
    return result;
}
