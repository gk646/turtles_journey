#include "OceanUi.h"

#include "data/GameData.h"
#include "magique/core/Draw.h"

OceanUI::OceanUI() : UIObject(10, 10) {}

void OceanUI::onDraw(const Rectangle& bounds)
{
    auto txt = "Cross the ocean to find your partner!";
    const auto& fnt = GetGameData().font;
    auto mid = magique::Point{T_CANVAS_X / 2, 20};
    const auto& colors = GetGameData().colors;
    magique::DrawCenteredPixelText(fnt, txt, mid.v(), 2, colors.background);
}