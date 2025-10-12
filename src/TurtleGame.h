#ifndef TURTLES_JOURNEY_TURTLEGAME_H
#define TURTLES_JOURNEY_TURTLEGAME_H

#include <cstring>
#include <vector>
#include "magique/core/Game.h"
#include "magique/util/Logging.h"
#include "stages/Stage.h"

enum class GameState : int
{
    None,
    MAIN_MENU,
    HIGH_SCORE_MENU,
    CREDITS,
    END_SCREEN,
    SCENE_1,
    SCENE_2,
    SCENE_3,
};

enum EntityType : uint16_t
{
    CAMERA,

    // Stage 1

    EGG,
    BEACH_TURTLE,

    // Stages 2

    STREET,
    CAR,
    TRUCK,
    WALKING_TURTLE,

    // Stage 3

    SWIM_TURTLE,
    PARTNER_TURTLE,

    // Good
    JELLY_FISH,
    PLANKTON,

    // Bad
    PLASTIC_BAG,
    OIL,
    TRASH_FISHNET,

    HEART,
};

enum class MapID : uint8_t
{
    Beach,
    Streets,
    Ocean,
};

enum class AnimationState : uint8_t
{
    Idle,
    Move,
};

enum class StorageID : int
{
    HIGHSCORES
};

inline AnimationState GetState(const char* name)
{
    if (strcmp(name, "Idle") == 0)
    {
        return AnimationState::Idle;
    }
    else if (strcmp(name, "Move") == 0)
    {
        return AnimationState::Move;
    }
    LOG_ERROR("NO animation state");
    return {};
}

inline AnimationState GetAnimState(magique::Point dir)
{
    if (dir.x == 0 && dir.y == 0)
    {
        return AnimationState::Idle;
    }
    else
    {
        return AnimationState::Move;
    }
}


struct TurtleGame final : magique::Game
{
    TurtleGame() : Game("A Turtles's Journey") {}
    void onStartup(magique::AssetLoader& loader) override;
    void onShutDown() override;
    void onLoadingFinished() override;
    void drawGame(GameState gameState, Camera2D& camera2D) override;
    void drawUI(GameState gameState) override;
    void updateGame(GameState gameState) override;
    void postTickUpdate(GameState gameState) override;
};

#endif // TURTLES_JOURNEY_TURTLEGAME_H