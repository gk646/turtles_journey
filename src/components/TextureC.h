#ifndef TURTLES_JOURNEY_TEXTUREC_H
#define TURTLES_JOURNEY_TEXTUREC_H

#include "magique/core/Types.h"

struct TextureC final
{
    magique::Point offset;
    bool flippedX = false;
    bool flippedY = false;
    magique::TextureRegion region;

    bool top = false;
};

#endif // TURTLES_JOURNEY_TEXTUREC_H