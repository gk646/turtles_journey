#include "ui/BeachUI.h"

#include "components/EggC.h"
#include "data/GameData.h"
#include "magique/core/Draw.h"

BeachUI::BeachUI() : UIObject(200, 50) {}

void BeachUI::onDraw(const Rectangle& bounds)
{
    auto txt = "Break the egg to hatch the turtle!";

    bool eggExists = false;
    for (auto e : magique::GetView<EggC>())
    {
        eggExists = true;
    }
    if (!eggExists)
    {
        txt = "Overcome the challenges on the beach!";
    }
    const auto& fnt = GetGameData().font;
    auto mid = magique::Point{T_CANVAS_X / 2, 20};
    const auto& colors = GetGameData().colors;
    magique::DrawPixelTextCentered(fnt, txt, mid.v(), 2, colors.background);
}