#include "TurtleGame.h"
#include "components/BeachTurtleC.h"
#include "components/CarC.h"
#include "components/EggC.h"
#include "components/ItemC.h"
#include "components/StreetC.h"
#include "components/SwimTurtleC.h"
#include "components/TextureC.h"
#include "components/WalkTurtle.h"
#include "data/GameData.h"
#include "loader/LoadTasks.h"
#include "magique/core/Core.h"
#include "magique/core/Debug.h"
#include "magique/ecs/ECS.h"
#include "magique/ecs/Scripting.h"
#include "scripts/Scripts.h"

void EntityLoader::execute(magique::AssetContainer& res)
{
    magique::SetEntityScript(EGG, new EggScript());
    magique::RegisterEntity(EGG,
                            [](entt::entity e, EntityType type)
                            {
                                magique::GiveCollisionRect(e, 42, 52);
                                magique::GiveComponent<EggC>(e);
                                magique::GiveActor(e);

                                auto& tex = magique::GiveComponent<TextureC>(e);
                                tex.region = GetGameData().eggs[0];

                                auto& pos = magique::GetComponent<magique::PositionC>(e);
                                pos.x -= 21;
                                pos.y -= 26;
                            });

    magique::SetEntityScript(CAMERA, new EmptyScript());

    magique::RegisterEntity(CAMERA,
                            [](entt::entity e, EntityType type)
                            {
                                magique::GiveActor(e);
                                magique::GiveCamera(e);
                            });

    magique::SetEntityScript(BEACH_TURTLE, new EmptyScript());
    magique::RegisterEntity(BEACH_TURTLE,
                            [](entt::entity e, EntityType type) { magique::GiveComponent<BeachTurtleC>(e); });


    magique::SetEntityScript(STREET, new StreetScript());
    magique::RegisterEntity(STREET,
                            [](entt::entity e, EntityType type)
                            {
                                auto& street = magique::GiveComponent<StreetC>(e);
                                street.goingUp = GetRandomValue(0, 100) > 50;
                                if (!street.goingUp)
                                {
                                    auto& pos = magique::GetComponent<magique::PositionC>(e);
                                    pos.y -= T_CANVAS_Y;
                                }
                                auto& tex = magique::GiveComponent<TextureC>(e);
                                if (street.goingUp)
                                {
                                    tex.flippedY = true;
                                    tex.offset = {0, -T_CANVAS_Y};
                                }
                                tex.region = GetGameData().street;
                            });

    magique::SetEntityScript(CAR, new CarScript());
    magique::RegisterEntity(CAR,
                            [](entt::entity e, EntityType type)
                            {
                                bool isTruck = GetRandomValue(0, 100) < 30;
                                auto& car = magique::GiveComponent<CarC>(e, isTruck);

                                float height = isTruck ? 50 : 40;
                                magique::GiveCollisionRect(e, StreetC::WIDTH, height);

                                float speed = isTruck ? 1.0 : 1.75F;
                                car.speed = speed;

                                auto& tex = magique::GiveComponent<TextureC>(e);

                                std::vector<magique::TextureRegion>& regions =
                                    isTruck ? GetGameData().truckTextures : GetGameData().carTextures;

                                auto rand = GetRandomValue(0, regions.size() - 1);
                                tex.region = regions[rand];
                                tex.top = true;
                            });

    magique::SetEntityScript(WALKING_TURTLE, new WalkTurtleScript());
    magique::RegisterEntity(WALKING_TURTLE,
                            [](entt::entity e, EntityType type)
                            {
                                magique::GiveCollisionRect(e, 20, 20);
                                auto& comp = magique::GiveComponent<WalkTurtleC>(e);
                                magique::GiveComponent<magique::AnimationC>(
                                    e, magique::AnimationC{GetGameData().walkTurtle, AnimationState::Idle});
                            });

    magique::SetEntityScript(SWIM_TURTLE, new SwimTurtleScript());
    magique::RegisterEntity(SWIM_TURTLE,
                            [](entt::entity e, EntityType type)
                            {
                                magique::GiveCollisionRect(e, 15, 8);
                                auto& comp = magique::GiveComponent<SwimTurtleC>(e);
                                magique::GiveComponent<magique::AnimationC>(
                                    e, magique::AnimationC{GetGameData().swimTurtle, AnimationState::Idle});
                            });


    magique::SetEntityScript(JELLY_FISH, new GoodItemScript());
    magique::SetEntityScript(PLANKTON, new GoodItemScript());

    magique::SetEntityScript(OIL, new BadItemScript());
    magique::SetEntityScript(TRASH_FISHNET, new BadItemScript());
    magique::SetEntityScript(PLASTIC_BAG, new BadItemScript());


    magique::RegisterEntity(JELLY_FISH,
                            [](entt::entity e, EntityType type)
                            {
                                auto& tex = magique::GiveComponent<TextureC>(e);
                                tex.region = GetGameData().jellyfish;
                                magique::GiveCollisionRect(e, tex.region.width, tex.region.height);
                                magique::GiveComponent<ItemC>(e, "Jellyfish");
                            });

    magique::RegisterEntity(PLANKTON,
                            [](entt::entity e, EntityType type)
                            {
                                auto& tex = magique::GiveComponent<TextureC>(e);
                                tex.region = GetGameData().plankton;
                                magique::GiveCollisionRect(e, tex.region.width, tex.region.height);
                                magique::GiveComponent<ItemC>(e, "Plankton");
                            });

    magique::RegisterEntity(OIL,
                            [](entt::entity e, EntityType type)
                            {
                                auto& tex = magique::GiveComponent<TextureC>(e);
                                tex.region = GetGameData().oil;
                                magique::GiveCollisionRect(e, tex.region.width, tex.region.height);
                                magique::GiveComponent<ItemC>(e, "Oil");
                            });
    magique::RegisterEntity(TRASH_FISHNET,
                            [](entt::entity e, EntityType type)
                            {
                                auto& tex = magique::GiveComponent<TextureC>(e);
                                tex.region = GetGameData().trashFishnet;
                                magique::GiveCollisionRect(e, tex.region.width, tex.region.height);
                                magique::GiveComponent<ItemC>(e, "Fishnet full of Trash");
                            });
    magique::RegisterEntity(PLASTIC_BAG,
                            [](entt::entity e, EntityType type)
                            {
                                auto& tex = magique::GiveComponent<TextureC>(e);
                                tex.region = GetGameData().plasticBag;
                                magique::GiveCollisionRect(e, tex.region.width, tex.region.height);
                                magique::GiveComponent<ItemC>(e, "Plastic Bag");
                            });

    magique::SetEntityScript(HEART, new HeartScript());
    magique::RegisterEntity(HEART,
                            [](entt::entity e, EntityType type)
                            {
                                auto& tex = magique::GiveComponent<TextureC>(e);
                                tex.region = GetGameData().heart;
                            });

    magique::SetEntityScript(PARTNER_TURTLE, new PartnerTurtleScript());
    magique::RegisterEntity(PARTNER_TURTLE,
                            [](entt::entity e, EntityType type)
                            {
                                magique::GiveCollisionRect(e, 15, 8);
                                auto& anim = magique::GiveComponent<magique::AnimationC>(
                                    e, magique::AnimationC{GetGameData().swimTurtle, AnimationState::Idle});
                                anim.setFlipX(true);
                            });

    magique::SetGameStateChangeCallback(
        [](GameState old, GameState newState)
        {
            if (old == newState)
            {
                return;
            }

            auto& data = GetGameData();
            if (data.currentStage != nullptr)
            {
                data.currentStage->onEnd();
            }

            if (newState == GameState::MAIN_MENU)
            {
                data.currentStage = &data.stage1;
                magique::GetComponent<magique::PositionC>(magique::GetPlayerEntity()).map = MapID::Beach;
            }
            else if (newState == GameState::SCENE_2)
            {
                data.currentStage = &data.stage2;
                magique::GetComponent<magique::PositionC>(magique::GetPlayerEntity()).map = MapID::Streets;
            }
            else if (newState == GameState::SCENE_3)
            {
                data.currentStage = &data.stage3;
            }

            if (data.currentStage != nullptr)
            {
                data.currentStage->onStart();
            }
        });
}