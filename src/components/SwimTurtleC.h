#ifndef TURTLES_JOURNEY_SWIMTURTLEC_H
#define TURTLES_JOURNEY_SWIMTURTLEC_H

#include "magique/config.h"
#include "magique/core/Types.h"

struct SwimTurtleC final
{
    static constexpr float MAX_SPEED = 40.0F / MAGIQUE_LOGIC_TICKS;
    static constexpr int ITEM_TIMER = 150;

    magique::Point accel;
    magique::Point veloc;
    magique::Point dir;

    bool badItem = false;
    bool goodItem = false;
    int itemCount = 0;
};


#endif // TURTLES_JOURNEY_SWIMTURTLEC_H