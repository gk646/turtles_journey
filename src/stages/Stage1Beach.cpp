#include "TurtleGame.h"
#include "data/GameData.h"
#include "magique/core/Camera.h"
#include "magique/core/Core.h"
#include "magique/core/Draw.h"
#include "magique/ecs/ECS.h"
#include "raylib/raylib.h"
#include "stages/Stage.h"

void Stage1Beach::onStart()
{
    registerEntity(magique::CreateEntity(EGG, 0, 0, MapID::Beach));
    auto& pos = magique::GetComponent<magique::PositionC>(magique::GetPlayerEntity());
    pos.map = MapID::Beach;
    pos.x = 0;
    pos.y = 0;
    magique::GetCamera().zoom = 1.0F;
}

void Stage1Beach::onEnd()
{
    cleanEntities();
    magique::DestroyEntities({BEACH_TURTLE});
}

void Stage1Beach::update(TurtleGame& game, GameState gameState) {}

void Stage1Beach::draw(TurtleGame& game, GameState gameState)
{
    EndMode2D();
    magique::DrawRegion(GetGameData().beach, {});
    BeginMode2D(magique::GetCamera());
}