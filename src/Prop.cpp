#include "Prop.h"
#include "raymath.h"

Prop::Prop(Texture2D tex, Vector2 pos, float scale)
    : texture{tex}, worldPos{pos}, scale{scale} {
}

void Prop::Render(Vector2 knightPos)
{
    Vector2 screenPos = Vector2Subtract(worldPos, knightPos);
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}

Rectangle Prop::getCollisionRec(Vector2 knightPos)
{
    Vector2 screenPos = Vector2Subtract(worldPos, knightPos);
    return Rectangle {
        screenPos.x,
        screenPos.y,
        texture.width * scale,
        texture.height * scale
    };
}