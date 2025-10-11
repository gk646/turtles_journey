#ifndef TURTLES_JOURNEY_MAINMENU_H
#define TURTLES_JOURNEY_MAINMENU_H

#include "magique/ui/UIObject.h"
#include "ui/PixelButton.h"

struct MainMenu : magique::UIObject
{
    MainMenu();
    void onDraw(const Rectangle& bounds) override;
    void onUpdate(const Rectangle& bounds, bool wasDrawn) override;

    bool up = false;
    float transparency = 1.0F;
    static constexpr float speed = 0.05F;
    PixelButton highScoreButton{100, 25, "Highscores"};
};

#endif // TURTLES_JOURNEY_MAINMENU_H