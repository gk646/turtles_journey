#include "TurtleGame.h"
#include "components/SwimTurtleC.h"
#include "scripts/Scripts.h"

void GoodItemScript::onTick(entt::entity self, bool updated) {}


void GoodItemScript::onDynamicCollision(entt::entity self, entt::entity other, magique::CollisionInfo& info)
{
    const auto& pos = magique::GetComponent<magique::PositionC>(other);
    if (pos.type != SWIM_TURTLE)
    {
        return;
    }
    magique::DestroyEntity(self);

    auto& swimT = magique::GetComponent<SwimTurtleC>(other);
    swimT.goodItem = true;
    swimT.itemCount = 0;
}