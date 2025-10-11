#include "TurtleGame.h"
#include "components/SwimTurtleC.h"
#include "magique/core/Debug.h"
#include "scripts/Scripts.h"
#include "ui/HighScoreUi.h"

void PartnerTurtleScript::onDynamicCollision(entt::entity self, entt::entity other, magique::CollisionInfo& info)
{
    const auto& oPos = magique::GetComponent<magique::PositionC>(other);
    if (oPos.type != SWIM_TURTLE)
    {
        return;
    }
    auto& swimT = magique::GetComponent<SwimTurtleC>(other);
    if (swimT.foundPartner)
    {
        return;
    }
    magique::CreateEntity(HEART, oPos.x, oPos.y, MapID::Ocean);
    swimT.foundPartner = true;
    HighScoreUI::times.push_back(magique::StopTimer(0));
}