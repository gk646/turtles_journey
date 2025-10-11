#include "PixelButton.h"
#include "data/GameData.h"
#include "magique/core/Draw.h"
#include "magique/util/RayUtils.h"

PixelButton::PixelButton(float width, float height, const char* text) : Button(width, height, magique::Anchor::NONE)
{
    if (text != nullptr)
    {
        setText(text);
    }
}

void PixelButton::onDraw(const Rectangle& bounds)
{
    const auto& colors = GetGameData().colors;
    Color background = getIsPressed(MOUSE_BUTTON_LEFT) ? colors.outline
       : getIsHovered()                                     ? colors.textPassive
                                                            : colors.backActive;

    if (getIsDisabled())
    {
        background = colors.background;
    }

    DrawRectangleRec(bounds, background);
    magique::DrawPixelOutline(bounds, colors.outline, colors.textPassive, colors.backActive, 1);

    const auto& fnt = GetGameData().font;

    if (text != nullptr)
    {
        float drawY = bounds.y + ((bounds.height - (float)fnt.baseSize) / 2.0F);
        magique::DrawCenteredPixelText(fnt, text, {bounds.x + bounds.width / 2.0F, drawY}, 1, colors.textHighlight);
    }
}

void PixelButton::setText(const char* newText) { text = newText; }