#include "ui/StreetUi.h"
#include "components/WalkTurtle.h"
#include "data/GameData.h"
#include "magique/core/Draw.h"
#include "magique/util/RayUtils.h"

StreetUI::StreetUI() : UIObject(10, 10) {}

void StreetUI::onDraw(const Rectangle& bounds)
{
    auto txt = "Cross the streets!";
    const auto& fnt = GetGameData().font;
    auto mid = magique::Point{T_CANVAS_X / 2, 20};
    const auto& colors = GetGameData().colors;
    magique::DrawCenteredPixelText(fnt, txt, mid.v(), 2, colors.background);

    float gap = 5;
    for (auto e : magique::GetView<WalkTurtleC>())
    {
        auto& walk = magique::GetComponent<WalkTurtleC>(e);
        auto region = GetGameData().turtleLife;

        auto totalWidth = WalkTurtleC::MAX_HEALTH * (region.width + gap);
        magique::Point pos = {T_CANVAS_X / 2 - totalWidth / 2, 40};

        Rectangle healthRect = {pos.x, pos.y, totalWidth, (float)region.height};

        continue;
        // DrawRectangleRec(healthRect, colors.outline);
        // magique::DrawPixelOutline(healthRect, colors.outline, colors.backActive, colors.textPassive);

        for (auto i = 0; i < WalkTurtleC::MAX_HEALTH; ++i)
        {
            Color color = ColorAlpha(WHITE, i >= walk.health ? 0.5F : 1.0F);
            magique::DrawRegion(region, pos, false, color);
            pos.x += region.width + gap;
        }
    }
}