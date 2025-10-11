#ifndef TURTLES_JOURNEY_STAGETRANSITION_H
#define TURTLES_JOURNEY_STAGETRANSITION_H

#include "TurtleGame.h"

struct StageTransition
{
    static void transitionTo(GameState gameState);

    static void draw();
    static void update();

private:
    static GameState target;

    static bool up;
    static bool done;
    static float transparency;
    static constexpr float speed = 0.02F;
};


#endif // TURTLES_JOURNEY_STAGETRANSITION_H