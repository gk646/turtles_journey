#ifndef TURTLES_JOURNEY_GAMEDATA_H
#define TURTLES_JOURNEY_GAMEDATA_H
#include "magique/assets/types/TileMap.h"
#include "magique/assets/types/TileSet.h"
#include "magique/assets/types/TileSheet.h"
#include "magique/core/Animations.h"
#include "magique/core/Particles.h"
#include "magique/persistence/GameSaveData.h"
#include "raylib/raylib.h"
#include "stages/Stage.h"

struct ColorData final
{
    // Shapes
    Color outline = Color{24, 20, 37, 255};
    Color background = Color{38, 43, 68, 255};
    Color backActive = Color{58, 68, 102, 255};
    Color backHighlight = Color{90, 105, 136, 255};

    // Text
    Color textPassive = Color{139, 155, 180, 255};
    Color text = Color{192, 203, 220, 255};
    Color textHighlight = Color{253, 255, 245, 255};

    // Utils
    Color error = Color{255, 0, 68, 255};
    Color errorPassive = Color{228, 59, 68, 255};
    Color warning = Color{254, 174, 52, 255};
    Color affirmative = Color{99, 199, 77, 255};

    Color ocean = Color{0, 153, 219};
};

struct GameData
{
    magique::GameSaveData save;
    Font font;
    ColorData colors;

    Stage* currentStage;
    Stage1Beach stage1{};
    Stage2Street stage2{};
    Stage3Ocean stage3{};

    // Stage 1

    std::vector<magique::TextureRegion> eggs;
    magique::TextureRegion bornTurtle;
    magique::TextureRegion beach;

    magique::ScreenEmitter eggParticles;

    // Stage 2

    std::vector<magique::TextureRegion> truckTextures;
    std::vector<magique::TextureRegion> carTextures;
    magique::TextureRegion street;
    magique::EntityAnimation walkTurtle{1};
    magique::TextureRegion turtleLife;

    magique::ScreenEmitter bloodParticles;

    // Stage 3

    magique::TileSet tileset;
    magique::TileSheet tilesheet;
    magique::TileMap tilemap;
    magique::TextureRegion ocean;

    magique::EntityAnimation swimTurtle{1};

    magique::TextureRegion plasticBag;
    magique::TextureRegion trashFishnet;
    magique::TextureRegion oil;

    magique::TextureRegion plankton;
    magique::TextureRegion jellyfish;

    magique::TextureRegion heart;

    magique::ScreenEmitter waterParticles;
    magique::ScreenEmitter yumParticles;

};

GameData& GetGameData();

#endif // TURTLES_JOURNEY_GAMEDATA_H