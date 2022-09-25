#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    worldPos = pos;
    width = static_cast<float>(texture.width/maxFrames);
    height = static_cast<float>(texture.height);
    speed = 3.5f;
}

void Enemy::tick(float deltaTime) 
{
    if (!getAlive()) return;

    velocity = Vector2Subtract(target->getScreenPos(), this->getScreenPos());
    if (Vector2Length(velocity) < radius || Vector2Length(velocity) > range) velocity = {};

    BaseCharacter::tick(deltaTime);

    if (CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}

