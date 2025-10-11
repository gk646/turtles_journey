#ifndef TURTLES_JOURNEY_STREETUI_H
#define TURTLES_JOURNEY_STREETUI_H
#include "magique/ui/UIObject.h"


struct StreetUI : magique::UIObject
{
    StreetUI();
    void onDraw(const Rectangle& bounds) override;
};


#endif // TURTLES_JOURNEY_STREETUI_H