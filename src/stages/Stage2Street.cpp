#include "TurtleGame.h"
#include "components/StreetC.h"
#include "components/WalkTurtle.h"
#include "data/GameData.h"
#include "magique/core/Draw.h"
#include "magique/core/StaticCollision.h"
#include "magique/util/RayUtils.h"
#include "raylib/raylib.h"
#include "stages/Stage.h"
#include "stages/StageTransition.h"

static Rectangle MAP_RECT;
static bool done = false;

void Stage2Street::onStart()
{
    done = false;
    float minGap = StreetC::WIDTH;
    float currX = 70;
    for (int i = 0; i < 15; ++i)
    {
        magique::CreateEntity(EntityType::STREET, currX, T_CANVAS_Y / 2, MapID::Streets);
        currX -= minGap + magique::GetRandomFloat(20, 55);
    }
    MAP_RECT = {currX - 200, -T_CANVAS_Y / 2, -currX + (T_CANVAS_X / 2) + 200, T_CANVAS_Y};
    magique::SetStaticWorldBounds(MAP_RECT);
    magique::CreateEntity(WALKING_TURTLE, T_CANVAS_Y / 2 - 50, 0, MapID::Streets);
}

void Stage2Street::onEnd()
{
    cleanEntities();
    magique::SetStaticWorldBounds({});
    magique::DestroyEntities({CAR, STREET, WALKING_TURTLE});
}

void Stage2Street::update(TurtleGame& game, GameState gameState)
{
    if (done)
    {
        return;
    }
    for (auto e : magique::GetView<WalkTurtleC>())
    {
        auto& pos = magique::GetComponent<magique::PositionC>(e);
        if (pos.x <= MAP_RECT.x + 100)
        {
            StageTransition::transitionTo(GameState::SCENE_3);
            done = true;
        }

        auto& walk = magique::GetComponent<WalkTurtleC>(e);
        auto& anim = magique::GetComponent<magique::AnimationC>(e);
        anim.setAnimationState(GetAnimState(walk.dir));
        if (walk.dir.x != 0 || walk.dir.y != 0)
        {
            anim.setFlipX(walk.dir.x > 0);
        }
    }
}

void Stage2Street::draw(TurtleGame& game, GameState gameState)
{
    for (int i = 1; i < 10; ++i)
    {
        magique::DrawRegion(GetGameData().beach, {T_CANVAS_X / 2 - 639.0F * i, -T_CANVAS_Y / 2});
    }
    magique::DrawParticles();
}