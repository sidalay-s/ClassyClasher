#ifndef PROP_H
#define PROP_H

#include "raylib.h"

class Prop
{
    private:
        Texture2D texture{};
        Vector2 worldPos{};
        float scale{3.f};
    public:
        Prop(Texture2D tex, Vector2 pos, float scale = 3.f);
        void Render(Vector2 knightPos);
        void setScale(float scale) {this->scale = scale;}
        Rectangle getCollisionRec(Vector2 knightPos);
};

#endif