#include "TurtleGame.h"
#include "components/ItemC.h"
#include "components/SwimTurtleC.h"
#include "data/GameData.h"
#include "scripts/Scripts.h"

void GoodItemScript::onTick(entt::entity self, bool updated) {}


void GoodItemScript::onDynamicCollision(entt::entity self, entt::entity other, magique::CollisionInfo& info)
{
    const auto& pos = magique::GetComponent<magique::PositionC>(other);
    if (pos.type != SWIM_TURTLE)
    {
        return;
    }

    auto& swimT = magique::GetComponent<SwimTurtleC>(other);
    swimT.goodItem = true;
    swimT.badItem = false;
    swimT.itemCount = 0;
    const auto& selP = magique::GetComponent<magique::PositionC>(self);

    swimT.lastItem = magique::GetComponent<ItemC>(self).name;

    magique::CreateScreenParticle(GetGameData().yumParticles, selP.getPosition(), 60);
    magique::DestroyEntity(self);
}