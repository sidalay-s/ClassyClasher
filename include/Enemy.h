#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
private:
    Character* target{};
    float damagePerSec{10.f};
    float radius{25.f};
    float range{125.f};
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    void tick(float deltaTime) override;
    void setTarget(Character* target) {this->target = target;}
    Vector2 getScreenPos() override;
};

#endif