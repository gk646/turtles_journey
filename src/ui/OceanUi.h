#ifndef TURTLES_JOURNEY_OCEANUI_H
#define TURTLES_JOURNEY_OCEANUI_H

#include "magique/ui/UIObject.h"

struct OceanUI : magique::UIObject
{
    OceanUI();
    void onDraw(const Rectangle& bounds) override;
};


#endif // TURTLES_JOURNEY_OCEANUI_H