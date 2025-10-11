#include "components/BeachTurtleC.h"
#include "data/GameData.h"
#include "magique/core/Draw.h"
#include "magique/ecs/ECS.h"
#include "magique/util/Logging.h"
#include "magique/util/RayUtils.h"
#include "raylib/raylib.h"
#include "stages/StageTransition.h"
#include "systems/SystemHandler.h"

Rectangle STREET_RECT = Rectangle{-250, 120, 500, KeyPrompt::KEY_SIZE};

static Rectangle GetKeyRect(const KeyPrompt& prompt)
{
    // aligned at the end of the rect
    Rectangle keyRect = {0, 0, KeyPrompt::KEY_SIZE, KeyPrompt::KEY_SIZE};
    keyRect.x = STREET_RECT.x + STREET_RECT.width - (prompt.pos + keyRect.width);
    keyRect.y = STREET_RECT.y;
    return keyRect;
}

static Rectangle GetAreaRect()
{
    return {STREET_RECT.x + KeyPrompt::AREA_START, STREET_RECT.y, KeyPrompt::AREA_WIDTH, KeyPrompt::KEY_SIZE};
}

void BeachTurtleSystem::draw()
{
    const auto& fnt = GetGameData().font;
    const auto& colors = GetGameData().colors;
    const auto areaRect = GetAreaRect();

    for (auto e : magique::GetView<BeachTurtleC>())
    {
        const auto& beachTurtle = magique::GetComponent<BeachTurtleC>(e);
        if (beachTurtle.done)
        {
            return;
        }
        const auto& pos = magique::GetComponent<magique::PositionC>(e);
        magique::DrawPixelOutline(STREET_RECT, colors.outline, colors.backHighlight, colors.textPassive);
        magique::DrawPixelOutline(areaRect, colors.outline, colors.affirmative, colors.textPassive);
        for (auto& prompt : beachTurtle.prompts)
        {
            auto keyRect = GetKeyRect(prompt);
            Color color = colors.backHighlight;
            if (CheckCollisionRecs(areaRect, keyRect))
            {
                color = colors.affirmative;
            }
            magique::DrawRectFrameFilled(keyRect, colors.background, color);
            auto drawPos =
                magique::Point{keyRect.x + keyRect.width / 2, keyRect.y + keyRect.height / 2 - (fnt.baseSize * 3) / 2};
            magique::DrawCenteredPixelText(fnt, TextFormat("%c", prompt.key), drawPos.v(), 3, colors.text);
        }
        magique::DrawRegion(GetGameData().bornTurtle, pos.getPosition());
        magique::DrawParticles();
    }
}

void BeachTurtleSystem::update()
{
    for (auto e : magique::GetView<BeachTurtleC>())
    {
        auto& pos = magique::GetComponent<magique::PositionC>(e);
        auto& beachTurtle = magique::GetComponent<BeachTurtleC>(e);
        if (beachTurtle.done)
        {
            return;
        }
        beachTurtle.delayCount++;
        if (beachTurtle.delayCount >= BeachTurtleC::DELAY)
        {
            auto rand = GetRandomValue(0, 25);
            beachTurtle.prompts.push_back({KEY_A + rand});
            beachTurtle.delayCount = GetRandomValue(-5, 25);
        }

        Rectangle areaRect = GetAreaRect();
        for (auto it = beachTurtle.prompts.begin(); it != beachTurtle.prompts.end();)
        {
            auto& prompt = *it;
            prompt.pos += 2;
            auto keyRect = GetKeyRect(prompt);

            if (CheckCollisionRecs(areaRect, keyRect) && IsKeyPressed(prompt.key))
            {
                it = beachTurtle.prompts.erase(it);
                beachTurtle.correctTips++;
                continue;
            }

            if (prompt.pos >= STREET_RECT.width)
            {
                it = beachTurtle.prompts.erase(it);
                continue;
            }
            ++it;
        }

        pos.y = beachTurtle.correctTips * -10;
        if (beachTurtle.correctTips >= BeachTurtleC::CORRECT_NEEDED)
        {
            beachTurtle.done = true;
            StageTransition::transitionTo(GameState::SCENE_2);
        }
    }
}