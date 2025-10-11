#include "TurtleGame.h"
#include "components/CarC.h"
#include "components/WalkTurtle.h"
#include "data/GameData.h"
#include "magique/core/Particles.h"
#include "scripts/Scripts.h"

void CarScript::onTick(entt::entity self, bool updated)
{
    auto& pos = magique::GetComponent<magique::PositionC>(self);
    const auto& car = magique::GetComponent<CarC>(self);

    if (car.goingUp)
    {
        pos.y -= car.speed;
    }
    else
    {
        pos.y += car.speed;
    }
}

void CarScript::onDynamicCollision(entt::entity self, entt::entity other, magique::CollisionInfo& info)
{
    auto& oPos = magique::GetComponent<magique::PositionC>(other);
    if (oPos.type != EntityType::WALKING_TURTLE)
    {
        return;
    }
    const auto& pos = magique::GetComponent<magique::PositionC>(self);
    const auto& car = magique::GetComponent<CarC>(self);
    auto& walkT = magique::GetComponent<WalkTurtleC>(other);

    oPos.x += 20;
    if (walkT.hitDelay <= WalkTurtleC::HIT_DELAY)
    {
        return;
    }

    magique::CreateScreenParticle(GetGameData().bloodParticles, oPos.getPosition(), 50);

    walkT.hitDelay = 0;

    if (car.isTruck)
    {
        walkT.health -= 2;
    }
    else
    {
        walkT.health--;
    }
}

void CarScript::onStaticCollision(entt::entity self, magique::ColliderInfo collider, magique::CollisionInfo& info) {}