#ifndef TURTLES_JOURNEY_HIGHSCOREUI_H
#define TURTLES_JOURNEY_HIGHSCOREUI_H

#include <vector>


#include "magique/ui/UIObject.h"

struct HighScoreUI : magique::UIObject
{
    HighScoreUI();

    void onDraw(const Rectangle& bounds) override;
    void onUpdate(const Rectangle& bounds, bool wasDrawn) override;

    static std::vector<uint64_t> times;
};


#endif // TURTLES_JOURNEY_HIGHSCOREUI_H