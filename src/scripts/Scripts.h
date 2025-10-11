#ifndef TURTLES_JOURNEY_SCRIPTS_H
#define TURTLES_JOURNEY_SCRIPTS_H

#include "magique/ecs/Scripting.h"

struct EggScript final : magique::EntityScript
{
    void onDestroy(entt::entity self) override;
    void onMouseEvent(entt::entity self) override;
};

struct StreetScript final : magique::EntityScript
{
    void onTick(entt::entity self, bool updated) override;
};

struct CarScript final : magique::EntityScript
{
    void onTick(entt::entity self, bool updated) override;
    void onDynamicCollision(entt::entity self, entt::entity other, magique::CollisionInfo& info) override;
    void onStaticCollision(entt::entity self, magique::ColliderInfo collider, magique::CollisionInfo& info) override;
};

struct WalkTurtleScript final : magique::EntityScript
{
    void onTick(entt::entity self, bool updated) override;
    void onKeyEvent(entt::entity self) override;
    void onStaticCollision(entt::entity self, magique::ColliderInfo collider, magique::CollisionInfo& info) override;
};

struct SwimTurtleScript final : magique::EntityScript
{
    void onTick(entt::entity self, bool updated) override;
    void onStaticCollision(entt::entity self, magique::ColliderInfo collider, magique::CollisionInfo& info) override;
};

struct GoodItemScript final : magique::EntityScript
{
    void onTick(entt::entity self, bool updated) override;
    void onDynamicCollision(entt::entity self, entt::entity other, magique::CollisionInfo& info) override;
};

struct PartnerTurtleScript final : magique::EntityScript
{
    void onDynamicCollision(entt::entity self, entt::entity other, magique::CollisionInfo& info) override;
};

struct BadItemScript final : magique::EntityScript
{
    void onTick(entt::entity self, bool updated) override;
    void onDynamicCollision(entt::entity self, entt::entity other, magique::CollisionInfo& info) override;
};

struct HeartScript final : magique::EntityScript
{
    static float start;

    void onTick(entt::entity self, bool updated) override
    {
        auto& pos = magique::GetComponent<magique::PositionC>(self);
        if (pos.y < start - 30)
        {
            return;
        }
        pos.y -= 0.3F;
    }

    void onCreate(entt::entity self) override
    {
        auto& pos = magique::GetComponent<magique::PositionC>(self);
        start = pos.y;
    }
};

inline float HeartScript::start = 0;

struct EmptyScript final : magique::EntityScript
{
};

#endif // TURTLES_JOURNEY_SCRIPTS_H