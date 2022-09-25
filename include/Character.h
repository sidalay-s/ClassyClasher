#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    float health{100.f};
public:
    Character(const int WindowDimensions[]);
    void tick(float deltaTime) override;
    Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRec() {return weaponCollisionRec;}
    float getHealth() const {return health;}
    void takeDamage(float damage);
};

#endif // CHARACTER_H