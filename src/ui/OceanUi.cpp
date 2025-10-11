#include "OceanUi.h"

#include "components/SwimTurtleC.h"
#include "data/GameData.h"
#include "magique/core/Draw.h"

OceanUI::OceanUI() : UIObject(10, 10) {}

void OceanUI::onDraw(const Rectangle& bounds)
{
    auto txt = "Cross the ocean to find your partner!";
    for (auto e : magique::GetView<SwimTurtleC>())
    {
        auto& swim = magique::GetComponent<SwimTurtleC>(e);
        if (swim.foundPartner)
        {
            return;
        }
    }
    const auto& fnt = GetGameData().font;
    auto mid = magique::Point{T_CANVAS_X / 2, 20};
    const auto& colors = GetGameData().colors;
    magique::DrawCenteredPixelText(fnt, txt, mid.v(), 2, colors.background);
}