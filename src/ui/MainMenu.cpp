#include "MainMenu.h"
#include "TurtleGame.h"
#include "data/GameData.h"
#include "magique/core/Core.h"
#include "magique/core/Debug.h"
#include "magique/core/Draw.h"
#include "magique/util/RayUtils.h"

MainMenu::MainMenu() : UIObject(200, 200, magique::Anchor::MID_CENTER)
{
    auto func = [](const struct Rectangle& bounds, int mouseButton)
    {
        if (magique::CheckMouseRect(bounds) && mouseButton == MOUSE_BUTTON_LEFT)
        {
            magique::SetGameState(GameState::HIGH_SCORE_MENU);
        }
    };
    highScoreButton.wireOnClick(func);

    auto func2 = [](const struct Rectangle& bounds, int mouseButton) { OpenURL("https://github.com/gk646/magique"); };
    magiqueButton.wireOnClick(func2);
}

void MainMenu::onDraw(const Rectangle& bounds)
{
    const auto& fnt = GetGameData().font;
    const auto& colors = GetGameData().colors;

    auto txt = "A Turtle's Journey";
    magique::DrawCenteredPixelText(fnt, txt, {T_CANVAS_X / 2, 50}, 3, colors.background);

    txt = "Tap to start";
    magique::DrawCenteredPixelText(fnt, txt, {T_CANVAS_X / 2, T_CANVAS_Y / 2}, 2,
                                   ColorAlpha(colors.text, transparency));

    highScoreButton.setAnchor(magique::Anchor::BOTTOM_RIGHT, 10);
    highScoreButton.draw();

    magiqueButton.setAnchor(magique::Anchor::BOTTOM_LEFT, 10);
    magiqueButton.draw();

    magique::DrawCenteredPixelText(fnt, "Created with magique", {T_CANVAS_X / 2, 300}, 2, colors.backHighlight);
}

void MainMenu::onUpdate(const Rectangle& bounds, bool wasDrawn)
{
    if (!wasDrawn)
    {
        return;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !magique::CheckMouseRect(highScoreButton.getBounds()) &&
        !magique::CheckMouseRect(magiqueButton.getBounds()))
    {
        magique::SetGameState(GameState::SCENE_1);
        // auto& stats = magique::GetComponent<GameStatsC>(magique::GetPlayerEntity());
        magique::StartTimer(0);
    }

    if (up)
    {
        transparency += speed;
    }
    else
    {
        transparency -= speed;
    }

    if (transparency <= 0.0F)
    {
        up = true;
    }
    if (transparency >= 1.0F)
    {
        up = false;
    }
}