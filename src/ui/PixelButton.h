#ifndef TURTLES_JOURNEY_PIXELBUTTON_H
#define TURTLES_JOURNEY_PIXELBUTTON_H

#include "magique/ui/controls/Button.h"

struct PixelButton : magique::Button
{
    PixelButton(float width, float height, const char* text = nullptr);
    void onDraw(const Rectangle& bounds) override;
    void setText(const char* text);

private:
    const char* text;
};

#endif // TURTLES_JOURNEY_PIXELBUTTON_H