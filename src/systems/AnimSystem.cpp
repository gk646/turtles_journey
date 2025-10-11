#include "magique/ecs/ECS.h"
#include "systems/SystemHandler.h"

void AnimSystem::draw()
{
    for (const auto e : magique::GetView<magique::AnimationC>())
    {
        const auto& anim = magique::GetComponent<magique::AnimationC>(e);
        const auto& pos = magique::GetComponent<magique::PositionC>(e);

        anim.drawCurrentFrame(pos.x, pos.y);
    }
}

void AnimSystem::update()
{
    for (const auto e : magique::GetView<magique::AnimationC>())
    {
        auto& anim = magique::GetComponent<magique::AnimationC>(e);
        anim.update();
    }
}