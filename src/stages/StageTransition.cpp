#include "stages/StageTransition.h"

#include "magique/core/Camera.h"
#include "magique/core/Core.h"
#include "raylib/raylib.h"

void StageTransition::transitionTo(GameState gameState)
{
    if (gameState != magique::GetGameState())
    {
        target = gameState;
    }
}

void StageTransition::draw()
{
    EndMode2D();
    DrawRectangleRec({0, 0, T_CANVAS_X, T_CANVAS_Y}, ColorAlpha(BLACK, transparency));
    BeginMode2D(magique::GetCamera());
}

void StageTransition::update()
{
    if (target != GameState::None)
    {
        if (transparency >= 1.0F)
        {
            magique::SetGameState(target);
            transparency -= speed;
            up = false;
            done = true;
        }

        if (transparency <= 0.0F)
        {
            if (done)
            {
                target = GameState::None;
                done = false;
                up = true;
                transparency = 0.0F;
                return;
            }
            up = true;
        }
        if (transparency >= 1.0F)
        {
            up = false;
        }

        if (up)
        {
            transparency += speed;
        }
        else
        {
            transparency -= speed;
        }
    }
}

bool StageTransition::up = true;
bool StageTransition::done = false;
float StageTransition::transparency = 0.0f;
GameState StageTransition::target = GameState::None;