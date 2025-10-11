#ifndef TURTLES_JOURNEY_STREETC_H
#define TURTLES_JOURNEY_STREETC_H

#include <vector>
#include "entt/entity/entity.hpp"

struct StreetC final
{
    static constexpr float WIDTH = 32;
    bool goingUp = false;
    std::vector<entt::entity> cars;
    int delay = 100;
    int delayCount = 0;
};


#endif // TURTLES_JOURNEY_STREETC_H