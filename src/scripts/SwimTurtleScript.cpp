#include "components/SwimTurtleC.h"
#include "data/GameData.h"
#include "magique/core/Camera.h"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "scripts/Scripts.h"

void SwimTurtleScript::onTick(entt::entity self, bool updated)
{
    auto& pos = magique::GetComponent<magique::PositionC>(self);
    auto& swimT = magique::GetComponent<SwimTurtleC>(self);

    swimT.itemCount++;
    float MAX_SPEED = SwimTurtleC::MAX_SPEED;
    const float DRAG_FACTOR = 0.99f;
    const float MIN_SPEED = 0.03f;

    if (swimT.goodItem)
    {
        MAX_SPEED *= 1.5F;
    }

    if (swimT.badItem)
    {
        MAX_SPEED *= 0.7F;
    }

    if (swimT.itemCount >= SwimTurtleC::ITEM_TIMER)
    {
        swimT.goodItem = false;
        swimT.badItem = false;
        swimT.lastItem = nullptr;
    }

    swimT.dir = {};

    if (IsKeyDown(KEY_W))
        swimT.dir.y = -1.0f;
    if (IsKeyDown(KEY_S))
        swimT.dir.y = 1.0f;
    if (IsKeyDown(KEY_A))
        swimT.dir.x = -1.0f;
    if (IsKeyDown(KEY_D))
        swimT.dir.x = 1.0f;

    float length = Vector2Length(swimT.dir.v());
    if (length > 0.0f)
    {
        swimT.dir = Vector2Scale(swimT.dir.v(), 1.0f / length);
    }

    swimT.accel.x = swimT.dir.x * swimT.MAX_SPEED;
    swimT.accel.y = swimT.dir.y * swimT.MAX_SPEED;

    if (swimT.veloc.x != 0.0f)
    {
        swimT.veloc.x *= DRAG_FACTOR;
        if (fabs(swimT.veloc.x) < MIN_SPEED)
            swimT.veloc.x = 0.0f;
    }
    if (swimT.veloc.y != 0.0f)
    {
        swimT.veloc.y *= DRAG_FACTOR;
        if (fabs(swimT.veloc.y) < MIN_SPEED)
            swimT.veloc.y = 0.0f;
    }

    swimT.veloc.x += swimT.accel.x;
    swimT.veloc.y += swimT.accel.y;

    float currentSpeed = Vector2Length(swimT.veloc.v());
    if (currentSpeed > MAX_SPEED)
    {
        swimT.veloc = Vector2Scale(Vector2Normalize(swimT.veloc.v()), MAX_SPEED);
    }

    pos.x += swimT.veloc.x;
    pos.y += swimT.veloc.y;

    auto& camPos = magique::GetComponent<magique::PositionC>(magique::GetCameraEntity());

    auto& data = GetGameData();
    const auto width = (float)data.tilemap.getWidth() * data.tileset.getTileSize();

    if (swimT.foundPartner)
    {
        camPos.x = pos.x;
        camPos.y = pos.y;
    }
    else
    {
        camPos.x = std::min(pos.x, width - T_CANVAS_X / 2.0F);
        camPos.x = std::max(camPos.x, T_CANVAS_X / 2.0F);
    }
}

void SwimTurtleScript::onStaticCollision(entt::entity self, magique::ColliderInfo collider,
                                         magique::CollisionInfo& info)
{

    AccumulateCollision(info);
}