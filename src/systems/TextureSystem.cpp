#include "components/TextureC.h"
#include "magique/core/Draw.h"
#include "magique/ecs/ECS.h"
#include "systems/SystemHandler.h"

void TextureSystem::draw()
{
    for (const auto e : magique::GetView<TextureC>())
    {
        const auto& pos = magique::GetComponent<magique::PositionC>(e);
        const auto& tex = magique::GetComponent<TextureC>(e);

        if (tex.top)
        {
            continue;
        }

        auto drawPos = pos.getPosition() + tex.offset;
        auto currentFrame = tex.region;
        const Rectangle dest = {drawPos.x, drawPos.y,
                                static_cast<float>(tex.flippedX ? -currentFrame.width : currentFrame.width),
                                static_cast<float>(tex.flippedY ? -currentFrame.height : currentFrame.height)};
        DrawRegionPro(currentFrame, dest, 0, {});
    }

    for (const auto e : magique::GetView<TextureC>())
    {
        const auto& pos = magique::GetComponent<magique::PositionC>(e);
        const auto& tex = magique::GetComponent<TextureC>(e);
        if (!tex.top)
        {
            continue;
        }

        auto drawPos = pos.getPosition() + tex.offset;
        auto currentFrame = tex.region;
        const Rectangle dest = {drawPos.x, drawPos.y,
                                static_cast<float>(tex.flippedX ? -currentFrame.width : currentFrame.width),
                                static_cast<float>(tex.flippedY ? -currentFrame.height : currentFrame.height)};
        DrawRegionPro(currentFrame, dest, 0, {});
    }
}


void TextureSystem::update() {}