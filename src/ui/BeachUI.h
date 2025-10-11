#ifndef TURTLES_JOURNEY_BEACHUI_H
#define TURTLES_JOURNEY_BEACHUI_H
#include "magique/ui/UIObject.h"


struct BeachUI : magique::UIObject
{
    BeachUI();
    void onDraw(const Rectangle& bounds) override;
};


#endif // TURTLES_JOURNEY_BEACHUI_H