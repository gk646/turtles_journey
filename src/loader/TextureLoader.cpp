#include "TurtleGame.h"
#include "data/GameData.h"
#include "loader/LoadTasks.h"
#include "magique/assets/AssetImport.h"
#include "magique/assets/container/AssetContainer.h"
#include "magique/core/StaticCollision.h"

void TextureLoader::execute(magique::AssetContainer& res)
{
    auto asset = res.getAsset("micro.png");
    auto fontImg = LoadImageFromMemory(".png", asset.getUData(), asset.getSize());
    GetGameData().font = LoadFontFromImage(fontImg, MAGENTA, 32);

    auto& data = GetGameData();

    // Stage 1

    data.eggs.push_back(magique::ImportTexture(res.getAsset("egg_1.png"), {}, 2));
    data.eggs.push_back(magique::ImportTexture(res.getAsset("egg_2.png"), {}, 2));
    data.eggs.push_back(magique::ImportTexture(res.getAsset("egg_3.png"), {}, 2));
    data.eggs.push_back(magique::ImportTexture(res.getAsset("egg_4.png"), {}, 2));
    data.eggs.push_back(magique::ImportTexture(res.getAsset("egg_5.png"), {}, 2));
    data.eggs.push_back(magique::ImportTexture(res.getAsset("egg_6.png"), {}, 2));

    data.bornTurtle = magique::ImportTexture(res.getAsset("turtle_born.png"));
    data.beach = magique::ImportTexture(res.getAsset("beach.png"));

    // Stage 2

    data.truckTextures.push_back(magique::ImportTexture(res.getAsset("truck_1.png")));

    data.carTextures.push_back(magique::ImportTexture(res.getAsset("car_1.png")));
    data.carTextures.push_back(magique::ImportTexture(res.getAsset("car_2.png")));
    data.carTextures.push_back(magique::ImportTexture(res.getAsset("car_3.png")));

    data.turtleLife = ImportTexture(res.getAsset("turtle_icon.png"));

    data.walkTurtle = magique::ImportAseprite(res.getAsset("walking_turtle.ase"), GetState);
    data.walkTurtle.offset = magique::Point{-6, -7};

    data.swimTurtle = magique::ImportAseprite(res.getAsset("swim_turtle.ase"), GetState);
    data.swimTurtle.offset = magique::Point{-9, -13};

    data.street = ImportTexture(res.getAsset("street.png"));

    // Stage 3

    data.tilemap = magique::ImportTileMap(res.getAsset("reef.tmj"));
    data.tilesheet = magique::ImportTileSheet(res.getAsset("tileset.png"), 8);
    data.tileset = magique::ImportTileSet(res.getAsset("tileset.tsj"));
    data.ocean = ImportTexture(res.getAsset("ocean.png"));

    magique::LoadGlobalTileSet(data.tileset);
    AddTileCollisions(MapID::Ocean, data.tilemap, {0, 1});

    data.plankton = ImportTexture(res.getAsset("plankton.png"));
    data.jellyfish = ImportTexture(res.getAsset("jelly_fish.png"));

    data.plasticBag = ImportTexture(res.getAsset("plastic_bag.png"));
    data.trashFishnet = ImportTexture(res.getAsset("trash_fishnet.png"));
    data.oil = ImportTexture(res.getAsset("oil.png"));

}