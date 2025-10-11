#include "components/WalkTurtle.h"
#include "magique/core/Camera.h"
#include "raylib/raylib.h"
#include "scripts/Scripts.h"

void WalkTurtleScript::onKeyEvent(entt::entity self)
{
    auto& pos = magique::GetComponent<magique::PositionC>(self);
    auto& walkT = magique::GetComponent<WalkTurtleC>(self);
    walkT.dir.x = 0.0f;
    walkT.dir.y = 0.0f;
    if (IsKeyDown(KEY_W))
    {
        pos.y -= walkT.speed;
        walkT.dir.y = -1.0f;
    }
    if (IsKeyDown(KEY_S))
    {
        pos.y += walkT.speed;
        walkT.dir.y = 1.0f;
    }
    if (IsKeyDown(KEY_A))
    {
        pos.x -= walkT.speed;
        walkT.dir.x = -1.0f;
    }
    if (IsKeyDown(KEY_D))
    {
        pos.x += walkT.speed;
        walkT.dir.x = 1.0f;
    }
}

void WalkTurtleScript::onStaticCollision(entt::entity self, magique::ColliderInfo collider,
                                         magique::CollisionInfo& info)
{
    AccumulateCollision(info);
}


void WalkTurtleScript::onTick(entt::entity self, bool updated)
{
    auto& camPos = magique::GetComponent<magique::PositionC>(magique::GetCameraEntity());
    const auto& pos = magique::GetComponent<magique::PositionC>(self);
    camPos.x = std::min(pos.x, 0.0F);
    auto& walkT = magique::GetComponent<WalkTurtleC>(self);
    walkT.hitDelay++;
}