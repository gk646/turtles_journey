#include "TurtleGame.h"
#include "data/GameData.h"
#include "loader/LoadTasks.h"
#include "magique/assets/AssetLoader.h"
#include "magique/assets/FileImports.h"
#include "magique/core/Core.h"
#include "magique/ecs/ECS.h"
#include "magique/ui/SceneManager.h"
#include "magique/util/RayUtils.h"
#include "raylib/raylib.h"
#include "stages/StageTransition.h"
#include "systems/SystemHandler.h"
#include "ui/HighScoreUi.h"

RenderTexture GAME_TEX;
GameSystemHandler HANDLER;
OverlaySystem OVERLAY;

void TurtleGame::onStartup(magique::AssetLoader& loader)
{
    loader.registerTask(new TextureLoader(), magique::THREAD_MAIN);
    loader.registerTask(new SettingsLoader(), magique::THREAD_ANY);
    loader.registerTask(new EntityLoader(), magique::THREAD_ANY);
    loader.registerTask(new UILoader(), magique::THREAD_MAIN);
    loader.registerTask(new ParticleLoader(), magique::THREAD_ANY);

    HANDLER.addSystem(new BeachTurtleSystem());
    HANDLER.addSystem(new TextureSystem());
    HANDLER.addSystem(new AnimSystem());

    GAME_TEX = LoadRenderTexture(T_CANVAS_X, T_CANVAS_Y);
}

void TurtleGame::onShutDown()
{
    std::string buff;
    magique::ExportJSON(HighScoreUI::times, buff);
    GetGameData().save.saveString(StorageID::HIGHSCORES, buff);
    magique::SaveToDisk(GetGameData().save, "turtle_highscores.save");
}

void TurtleGame::onLoadingFinished()
{
    auto player = magique::CreateEntity(CAMERA, 0, 0, MapID::Beach);
    magique::SetPlayerEntity(player);
    magique::SetGameState(GameState::MAIN_MENU);
}

void TurtleGame::drawGame(GameState gameState, Camera2D& camera2D)
{
    BeginTextureMode(GAME_TEX);
    ClearBackground(GRAY);
    BeginMode2D(camera2D);
    {
        auto* stage = GetGameData().currentStage;
        if (stage != nullptr)
        {
            stage->draw(*this, magique::GetGameState());
        }
        HANDLER.draw();
        if (stage != nullptr)
        {
            stage->drawOnTop();
        }
        StageTransition::draw();
    }
    EndMode2D();
}

void TurtleGame::drawUI(GameState gameState)
{
    auto& scene = magique::GetSceneManager().getScene(gameState);
    scene.draw();
    OVERLAY.draw();

    EndTextureMode();

    auto canvas = magique::Point{T_CANVAS_X, T_CANVAS_Y};
    const auto display = magique::Point{(float)GetScreenWidth(), (float)GetScreenHeight()};
    auto scale = magique::Point{display.x / canvas.x, display.y / canvas.y};
    if (scale < 0)
    {
        scale = {1, 1};
    }
    scale.floor();
    if (scale.x < scale.y)
    {
        scale.y = scale.x;
    }
    if (scale.y < scale.x)
    {
        scale.x = scale.y;
    }
    canvas *= scale;
    SetMouseScale(1 / scale.x, 1 / scale.y);
    auto drawPos = magique::GetCenteredPos({0, 0, display.x, display.y}, canvas.x, canvas.y);
    SetMouseOffset((int)-drawPos.x, (int)-drawPos.y);
    magique::DrawRenderTexture(GAME_TEX, drawPos, scale.x, WHITE);
}

void TurtleGame::updateGame(GameState gameState)
{
    if (IsKeyPressed(KEY_F11))
    {
        magique::ToggleFullscreenEx();
    }
    auto* stage = GetGameData().currentStage;
    if (stage != nullptr)
    {
        stage->update(*this, magique::GetGameState());
    }
    HANDLER.update();
}

void TurtleGame::postTickUpdate(GameState gameState) { StageTransition::update(); }