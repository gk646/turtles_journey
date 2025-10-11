#include "TurtleGame.h"
#include "components/ItemC.h"
#include "components/SwimTurtleC.h"
#include "data/GameData.h"
#include "scripts/Scripts.h"

void BadItemScript::onTick(entt::entity self, bool updated) {}

void BadItemScript::onDynamicCollision(entt::entity self, entt::entity other, magique::CollisionInfo& info)
{
    const auto& pos = magique::GetComponent<magique::PositionC>(other);
    if (pos.type != SWIM_TURTLE)
    {
        return;
    }

    auto& swimT = magique::GetComponent<SwimTurtleC>(other);
    swimT.badItem = true;
    swimT.goodItem = false;
    swimT.itemCount = 0;
    swimT.lastItem = magique::GetComponent<ItemC>(self).name;
    const auto& selP = magique::GetComponent<magique::PositionC>(self);
    magique::CreateScreenParticle(GetGameData().bloodParticles, selP.getPosition(), 60);
    magique::DestroyEntity(self);
}