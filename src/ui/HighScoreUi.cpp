#include "HighScoreUi.h"
#include "TurtleGame.h"
#include "data/GameData.h"
#include "magique/core/Core.h"
#include "magique/core/Draw.h"
#include "raylib/raylib.h"

HighScoreUI::HighScoreUI() : UIObject(10, 10) {}

void HighScoreUI::onDraw(const Rectangle& bounds)
{
    const auto& fnt = GetGameData().font;
    const auto& colors = GetGameData().colors;
    auto mid = magique::Point{T_CANVAS_X / 2, 40};

    auto sorted = times;
    std::ranges::sort(sorted);
    for (auto time : sorted)
    {
        int minutes = static_cast<int>(time / 60000000000);
        int seconds = static_cast<int>((time % 60000000000) / 1000000000);
        int milliseconds = static_cast<int>((time % 1000000000) / 1000000);

        auto txt = TextFormat("%d:%02d:%04d", minutes, seconds, milliseconds);
        magique::DrawCenteredPixelText(fnt, txt, mid.v(), 2, colors.background);
        mid.y += 13;
    }

    if (times.empty())
    {
        magique::DrawCenteredPixelText(fnt, "No times", mid.v(), 2, colors.background);
    }
}

void HighScoreUI::onUpdate(const Rectangle& bounds, bool wasDrawn)
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        magique::SetGameState(GameState::MAIN_MENU);
    }
}


std::vector<uint64_t> HighScoreUI::times = {};