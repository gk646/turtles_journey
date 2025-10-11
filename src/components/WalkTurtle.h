#ifndef TURTLES_JOURNEY_WALKTURTLE_H
#define TURTLES_JOURNEY_WALKTURTLE_H

#include "magique/config.h"
#include "magique/core/Types.h"

struct WalkTurtleC final
{
    static constexpr float MAX_HEALTH = 5;
    static constexpr float HIT_DELAY = 50;
    int health = MAX_HEALTH;
    float speed = 75.0F / MAGIQUE_LOGIC_TICKS;
    magique::Point dir;
    int hitDelay = 0;
};
#endif // TURTLES_JOURNEY_WALKTURTLE_H