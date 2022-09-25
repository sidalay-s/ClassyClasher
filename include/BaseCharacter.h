#ifndef BASECHARACTER_H
#define BASECHARACTER_H

#include "raylib.h"

class BaseCharacter
{
private:
    bool Alive{true};
protected:
    Texture2D texture{};
    Texture2D idle{};
    Texture2D run{};
    // sprite pos on map
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    //  1 : facing right, -1 : facing left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f/12.f};
    float speed{5.f};
    float width{};
    float height{};
    float scale{4.f};
    Vector2 velocity{};
public:
    BaseCharacter();
    Vector2 getWorldPos() {return worldPos;}
    virtual Vector2 getScreenPos() = 0;
    void undoMovement();
    Rectangle getCollisionRec();
    virtual void tick(float deltaTime);
    bool getAlive() {return Alive;}
    void setAlive(bool isAlive) {Alive = isAlive;}
};

#endif