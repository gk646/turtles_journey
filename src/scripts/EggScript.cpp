#include "TurtleGame.h"
#include "components/EggC.h"
#include "components/TextureC.h"
#include "data/GameData.h"
#include "magique/core/CollisionDetection.h"
#include "magique/core/Core.h"
#include "raylib/raylib.h"
#include "scripts/Scripts.h"

void EggScript::onDestroy(entt::entity self)
{
    if (magique::GetGameState() != GameState::SCENE_1)
    {
        return;
    }
    const auto& pos = magique::GetComponent<magique::PositionC>(self);
    magique::CreateEntity(EntityType::BEACH_TURTLE, pos.x, pos.y, pos.map);
}

void EggScript::onMouseEvent(entt::entity self)
{
    if (magique::GetGameState() != GameState::SCENE_1)
    {
        return;
    }
    const auto& pos = magique::GetComponent<magique::PositionC>(self);
    const auto& col = magique::GetComponent<magique::CollisionC>(self);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && magique::CheckCollisionEntityMouse(pos, col))
    {
        auto& egg = magique::GetComponent<EggC>(self);
        egg.health -= 1;
        auto& tex = magique::GetComponent<TextureC>(self);
        int itsPerTex = EggC::MAX_HEALTH / GetGameData().eggs.size();
        int itCount = EggC::MAX_HEALTH - egg.health;
        int texCount = itCount / itsPerTex;
        texCount = std::min(texCount, (int)GetGameData().eggs.size() - 1);
        tex.region = GetGameData().eggs.at(texCount);

        magique::CreateScreenParticle(GetGameData().eggParticles, pos.getPosition(), 100);
        if (egg.health <= 0)
        {
            magique::DestroyEntity(self);
        }
    }
}