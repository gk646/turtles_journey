#ifndef TURTLES_JOURNEY_BEACHTURTLEC_H
#define TURTLES_JOURNEY_BEACHTURTLEC_H

#include <vector>

struct KeyPrompt final
{
    static constexpr float KEY_SIZE = 50;
    static constexpr float AREA_START = 50;
    static constexpr float AREA_WIDTH = 50;

    int key;
    float pos = KEY_SIZE;
};

struct BeachTurtleC final
{
    static constexpr int DELAY = 45;
    static constexpr int CORRECT_NEEDED = 15;

    int delayCount = 0;
    int correctTips;
    std::vector<KeyPrompt> prompts;
    bool done = false;
};

#endif // TURTLES_JOURNEY_BEACHTURTLEC_H