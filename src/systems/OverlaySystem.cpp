#include "TurtleGame.h"
#include "data/GameData.h"
#include "fwd.h"
#include "magique/core/Camera.h"
#include "magique/core/Core.h"
#include "magique/core/Debug.h"
#include "magique/core/Draw.h"
#include "systems/SystemHandler.h"

void OverlaySystem::draw()
{
    auto state = magique::GetGameState();
    if (state == GameState::MAIN_MENU || state == GameState::HIGH_SCORE_MENU)
    {
        return;
    }
    auto time = magique::GetTimerTime(0);
    int minutes = static_cast<int>(time / 60000000000);
    int seconds = static_cast<int>((time % 60000000000) / 1000000000);
    int milliseconds = static_cast<int>((time % 1000000000) / 1000000);

    auto txt = TextFormat("%d:%02d:%04d", minutes, seconds, milliseconds);
    const auto& fnt = GetGameData().font;
    const auto& colors = GetGameData().colors;
    EndMode2D();
    magique::DrawRightBoundPixelText(fnt, txt, {T_CANVAS_X - 10, 10}, 2, colors.background);
    BeginMode2D(magique::GetCamera());
}

void OverlaySystem::update() {}