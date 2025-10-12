#include "TurtleGame.h"
#include "components/SwimTurtleC.h"
#include "data/GameData.h"
#include "magique/core/Camera.h"
#include "magique/core/Core.h"
#include "magique/core/Debug.h"
#include "magique/core/Draw.h"
#include "magique/core/StaticCollision.h"
#include "magique/util/RayUtils.h"
#include "stages/Stage.h"
#include "stages/StageTransition.h"
#include "ui/HighScoreUi.h"

static Rectangle STAGE_RECT;
int waitCounter = 0;

inline magique::Point PickRandomPos(const Rectangle& rect)
{
    magique::Point ret{rect.x, rect.y};
    ret.x += GetRandomValue(0, rect.width);
    ret.y += GetRandomValue(0, rect.height);
    return ret;
}

void Stage3Ocean::onStart()
{
    waitCounter = 0;
    magique::CreateEntity(SWIM_TURTLE, 192 * 8, 21 * 8, MapID::Ocean);
    auto& pos = magique::GetComponent<magique::PositionC>(magique::GetPlayerEntity());
    pos.map = MapID::Ocean;
    pos.x = 192 * 8;
    pos.y = 21 * 8 + 12;

    auto& data = GetGameData();
    const auto width = (float)data.tilemap.getWidth() * data.tileset.getTileSize();
    STAGE_RECT = {0, 0, width, T_CANVAS_Y};
    magique::SetStaticWorldBounds(STAGE_RECT);

    for (auto& obj : GetGameData().tilemap.getObjects(0))
    {
        auto pos = PickRandomPos(Rectangle{obj.x, obj.y, obj.width, obj.height});
        EntityType type{};
        if (strcmp(obj.getName(), "trash_fishnet") == 0)
        {
            type = TRASH_FISHNET;
        }
        else if (strcmp(obj.getName(), "plastic_bag") == 0)
        {
            type = PLASTIC_BAG;
        }
        else if (strcmp(obj.getName(), "oil") == 0)
        {
            type = OIL;
        }
        else if (strcmp(obj.getName(), "plankton") == 0)
        {
            type = PLANKTON;
        }
        else if (strcmp(obj.getName(), "jelly_fish") == 0)
        {
            type = JELLY_FISH;
        }
        else
        {
            LOG_ERROR("Wrong name");
        }
        magique::CreateEntity(type, pos.x, pos.y, MapID::Ocean);
    }
    magique::CreateEntity(PARTNER_TURTLE, 5 * 8, 21 * 8, MapID::Ocean);
}

void Stage3Ocean::onEnd()
{
    magique::DestroyEntities(
        {SWIM_TURTLE, HEART, PARTNER_TURTLE, JELLY_FISH, PLANKTON, TRASH_FISHNET, OIL, PLASTIC_BAG});
    magique::SetStaticWorldBounds({});
}

void Stage3Ocean::draw(TurtleGame& game, GameState gameState)
{
    magique::DrawParticles();
    const auto& data = GetGameData();
    for (int i = 0; i < data.tilemap.getTileLayerCount(); ++i)
    {
        magique::DrawTileMap(data.tilemap, data.tilesheet, i);
    }
}

void Stage3Ocean::drawOnTop()
{
    const auto& fnt = GetGameData().font;
    const auto& colors = GetGameData().colors;
    for (int i = 0; i < 15; ++i)
    {
        Rectangle rect = {640.0F * i, 0, 640, 360};
        DrawRectangleRec(rect, ColorAlpha(colors.ocean, 0.2));
    }

    for (auto e : magique::GetView<SwimTurtleC>())
    {
        auto& swim = magique::GetComponent<SwimTurtleC>(e);
        if (swim.foundPartner)
        {
            auto time = HighScoreUI::times.back();
            int minutes = static_cast<int>(time / 60000000000);
            int seconds = static_cast<int>((time % 60000000000) / 1000000000);
            int milliseconds = static_cast<int>((time % 1000000000) / 1000000);

            EndMode2D();
            auto txt = TextFormat("%d:%02d:%04d", minutes, seconds, milliseconds);
            magique::DrawRightBoundPixelText(fnt, txt, {T_CANVAS_X / 2, 150}, 2, colors.textPassive);
            magique::DrawCenteredPixelText(fnt, "You found your partner!", {T_CANVAS_X / 2, 100}, 2, colors.background);
            BeginMode2D(magique::GetCamera());
        }

        if (swim.lastItem != nullptr)
        {
            const char* txt = nullptr;
            if (swim.badItem)
            {
                txt = TextFormat("Ewww, bad %s!", swim.lastItem);
            }
            else
            {
                txt = TextFormat("Yum yum, good %s", swim.lastItem);
            }
            EndMode2D();
            magique::DrawCenteredPixelText(fnt, txt, {T_CANVAS_X / 2, 100}, 2, colors.background);
            BeginMode2D(magique::GetCamera());
        }
    }
}

void Stage3Ocean::update(TurtleGame& game, GameState gameState)
{
    auto& data = GetGameData();
    const auto width = (float)data.tilemap.getWidth() * data.tileset.getTileSize();
    auto rand = magique::Point{magique::GetRandomFloat(0, width), magique::GetRandomFloat(50, 360)};
    magique::CreateScreenParticle(data.waterParticles, rand, 3);

    for (auto e : magique::GetView<SwimTurtleC>())
    {
        auto& pos = magique::GetComponent<magique::PositionC>(e);
        auto& swim = magique::GetComponent<SwimTurtleC>(e);
        auto& anim = magique::GetComponent<magique::AnimationC>(e);

        auto state = GetAnimState(swim.dir);
        anim.setAnimationState(state);
        if (swim.dir.x != 0)
        {
            anim.setFlipX(swim.veloc.x > 0);
        }

        if (swim.foundPartner)
        {

            if (magique::GetCamera().zoom <= 1.5F)
            {
                magique::GetCamera().zoom += 0.01;
            }
            waitCounter++;
        }
    }

    if (waitCounter > 200)
    {
        StageTransition::transitionTo(GameState::MAIN_MENU);
    }
}