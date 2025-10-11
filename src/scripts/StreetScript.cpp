#include "TurtleGame.h"
#include "components/CarC.h"
#include "components/StreetC.h"
#include "components/TextureC.h"
#include "raylib/raylib.h"
#include "scripts/Scripts.h"

void StreetScript::onTick(entt::entity self, bool updated)
{
    const auto& pos = magique::GetComponent<magique::PositionC>(self);
    auto& street = magique::GetComponent<StreetC>(self);
    street.delayCount++;
    if (street.delayCount >= street.delay)
    {
        auto ent = magique::CreateEntity(EntityType::CAR, pos.x, pos.y, pos.map);
        street.delayCount = 0;
        street.delay = GetRandomValue(65, 90);
        auto& car = magique::GetComponent<CarC>(ent);
        if (car.isTruck)
        {
            street.delayCount += 15;
        }
        car.goingUp = street.goingUp;
        if (car.goingUp)
        {
            auto& tex = magique::GetComponent<TextureC>(ent);
            tex.flippedY = true;
        }
        street.cars.push_back(ent);
    }

    for (auto it = street.cars.begin(); it != street.cars.end();)
    {
        auto car = *it;
        const auto& carPos = magique::GetComponent<magique::PositionC>(car);
        auto& carC = magique::GetComponent<CarC>(car);
        if (carPos.y <= -T_CANVAS_Y / 2 - 50 || carPos.x >= T_CANVAS_X / 2 + 50)
        {
            magique::DestroyEntity(car);
            it = street.cars.erase(it);
            continue;
        }
        ++it;
    }
}