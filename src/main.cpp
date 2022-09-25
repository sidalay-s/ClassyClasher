#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "Prop.h"
#include <string>

int main() 
{   
    const int WindowDimensions[2] {384,384};
    InitWindow(WindowDimensions[0], WindowDimensions[1], "Classy Clasher");
    SetTargetFPS(60);

    Texture2D WorldMap {LoadTexture("nature_tileset/worldMap2.png")};
    // position of map on window
    Vector2 mapPos{0.0,0.0};
    const float mapScale{4.f};

    Character knight{WindowDimensions};
    // knight.setScreenPos(WindowDimensions);


    Enemy goblin {
        Vector2{1000.f,600.f}, 
        LoadTexture("characters/goblin_idle_spritesheet.png"), 
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    Enemy goblinTwo {
        Vector2{300.f,500.f}, 
        LoadTexture("characters/goblin_idle_spritesheet.png"), 
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    Enemy slime {
        Vector2{600.f,900.f}, 
        LoadTexture("characters/slime_idle_spritesheet.png"), 
        LoadTexture("characters/slime_run_spritesheet.png")
    };

    Enemy slimeTwo {
        Vector2{400.f,1500.f}, 
        LoadTexture("characters/slime_idle_spritesheet.png"), 
        LoadTexture("characters/slime_run_spritesheet.png")
    };

    Enemy* enemies[] = {&goblin, &goblinTwo, &slime, &slimeTwo};

    // goblin.setTarget(&knight);

    Prop props[4] {
        Prop{LoadTexture("nature_tileset/Rock.png"), Vector2{300.f, 200.f}},
        Prop{LoadTexture("nature_tileset/Rock.png"), Vector2{500.f, 200.f}, 4.f},
        Prop{LoadTexture("nature_tileset/Sign.png"), Vector2{700.f, 200.f}},
        Prop{LoadTexture("nature_tileset/Sign.png"), Vector2{900.f, 200.f}, 1.f}
    };

    SetExitKey(KEY_NULL);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        

        // draw the map
        DrawTextureEx(WorldMap, mapPos, 0.f, mapScale, WHITE);

        // draw the props
        for (auto& prop:props)
        {
            prop.Render(knight.getWorldPos());
        }

        if (!knight.getAlive())
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightsHealth {"Health: "};
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        knight.tick(GetFrameTime());
        // check map bounds
        if (knight.getWorldPos().x < 0.f || 
            knight.getWorldPos().y < 0.f || 
            knight.getWorldPos().x + WindowDimensions[0] > WorldMap.width * mapScale ||
            knight.getWorldPos().y + WindowDimensions[1] > WorldMap.height * mapScale )
        {
            knight.undoMovement();
        }

        // collision checker
        for (auto& prop:props)
        {
            if(CheckCollisionRecs(knight.getCollisionRec(), prop.getCollisionRec(knight.getWorldPos())))
            {
                knight.undoMovement();
            }
        }

        for (auto& enemy:enemies)
        {
            enemy->setTarget(&knight);
            enemy->tick(GetFrameTime());

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        // goblin.tick(GetFrameTime());

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        // {
        //     if (CheckCollisionRecs(goblin.getCollisionRec(), knight.getWeaponCollisionRec()))
        //     {
        //         goblin.setAlive(false);
        //     }
        // }

        EndDrawing();
    }
    UnloadTexture(WorldMap);
    CloseWindow();
}