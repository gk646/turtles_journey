#include "TurtleGame.h"
#include "loader/LoadTasks.h"
#include "magique/ui/SceneManager.h"
#include "ui/BeachUI.h"
#include "ui/MainMenu.h"
#include "ui/OceanUi.h"
#include "ui/StreetUi.h"

void UILoader::execute(magique::AssetContainer& res)
{
    auto& beach = magique::GetSceneManager().getScene(GameState::SCENE_1);
    beach.addObject(new BeachUI());

    auto& mainMenu = magique::GetSceneManager().getScene(GameState::MAIN_MENU);
    mainMenu.addObject(new MainMenu());

    auto& street = magique::GetSceneManager().getScene(GameState::SCENE_2);
    street.addObject(new StreetUI());

    auto& ocean = magique::GetSceneManager().getScene(GameState::SCENE_3);
    ocean.addObject(new OceanUI());
}