#include "TurtleGame.h"
#include "data/GameData.h"
#include "fwd.h"
#include "loader/LoadTasks.h"
#include "magique/assets/FileImports.h"
#include "magique/core/Camera.h"
#include "magique/core/Debug.h"
#include "magique/persistence/GameSaveData.h"
#include "magique/ui/UI.h"
#include "magique/util/RayUtils.h"
#include "raylib/raylib.h"
#include "ui/HighScoreUi.h"

void SettingsLoader::execute(magique::AssetContainer& res)
{
    //  magique::SetShowHitboxes(true);
    //  magique::SetShowCompassOverlay(true);

    magique::SetUISourceResolution(T_CANVAS_X, T_CANVAS_Y);
    magique::SetUITargetResolution(T_CANVAS_X, T_CANVAS_Y);

    magique::SetCameraViewOffset(T_CANVAS_X / 2, T_CANVAS_Y / 2);

    magique::SetCameraSmoothing(0.1);

    magique::SetShowPerformanceOverlay(false);
    magique::ToggleFullscreenEx();


    magique::LoadFromDisk(GetGameData().save, "turtle_highscores.save");

    auto buff = GetGameData().save.getStringOrElse(StorageID::HIGHSCORES);
    if (buff.empty())
    {
        return;
    }
    magique::ImportJSON(buff.c_str(), HighScoreUI::times);
}