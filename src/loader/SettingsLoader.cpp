#include "fwd.h"
#include "loader/LoadTasks.h"
#include "magique/core/Camera.h"
#include "magique/core/Debug.h"
#include "magique/ui/UI.h"

void SettingsLoader::execute(magique::AssetContainer& res)
{
    magique::SetShowHitboxes(true);
     magique::SetShowCompassOverlay(true);

    magique::SetUISourceResolution(T_CANVAS_X, T_CANVAS_Y);
    magique::SetUITargetResolution(T_CANVAS_X, T_CANVAS_Y);

    magique::SetCameraViewOffset(T_CANVAS_X / 2, T_CANVAS_Y / 2);

    magique::SetCameraSmoothing(0.1);
}