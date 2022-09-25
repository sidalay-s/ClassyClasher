#include "Character.h"
#include "raymath.h"

Character::Character(const int WindowDimensions[])
    : windowWidth{WindowDimensions[0]}, windowHeight{WindowDimensions[1]}
{
    texture = LoadTexture("characters/knight_idle_spritesheet.png");
    idle = LoadTexture("characters/knight_idle_spritesheet.png");
    run = LoadTexture("characters/knight_run_spritesheet.png");
    width = static_cast<float>(texture.width/maxFrames);
    height = static_cast<float>(texture.height);
}

Vector2 Character::getScreenPos() 
{
    return Vector2 {
        static_cast<float>(windowWidth)/2.f - scale * (0.5f * this->width),
        static_cast<float>(windowHeight)/2.f - scale * (0.5f * this->height)
    };
}

void Character::tick(float deltaTime) 
{
    if (!getAlive()) return;

    if (IsKeyDown(KEY_A)) velocity.x -= 1.0;
    if (IsKeyDown(KEY_D)) velocity.x += 1.0;
    if (IsKeyDown(KEY_W)) velocity.y -= 1.0;
    if (IsKeyDown(KEY_S)) velocity.y += 1.0;

    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (rightLeft > 0.f)
    {
        origin = {0.f, weapon.height * 3.f};
        offset = {40.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * 3.f,
            weapon.width * 3.f,
            weapon.height * 3.f
        };
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = 35.f : rotation = 0.f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * 3.f};
        offset = {40.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + (offset.x - 15.f) - weapon.width * 3.f,
            getScreenPos().y + offset.y - weapon.height * 3.f,
            weapon.width * 3.f,
            weapon.height * 3.f
        };
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = -25.f : rotation = 0.f;
    }

    //draw the sword
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * 3.f, weapon.height * 3.f};
    DrawTexturePro(weapon, source, dest, origin, rotation, BROWN);

    // DrawRectangleLines(
    //     weaponCollisionRec.x,
    //     weaponCollisionRec.y,
    //     weaponCollisionRec.width,
    //     weaponCollisionRec.height,
    //     RED
    // );
}

void Character::takeDamage(float damage) 
{
    health -= damage;
    if (health <= 0.f) setAlive(false);
}
