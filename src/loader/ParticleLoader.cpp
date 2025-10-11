#include "data/GameData.h"
#include "loader/LoadTasks.h"


void ParticleLoader::execute(magique::AssetContainer& res)
{
    auto& data = GetGameData();

    auto& egg = data.eggParticles;
    egg.setEmissionShape(magique::Shape::RECT, 42, 52);
    egg.setGravity(0, -1.0F);
    egg.setColorPool({Color{245, 117, 122, 200}, Color{254, 174, 32, 200}, data.colors.textHighlight, data.colors.text,
                      data.colors.textPassive});
    egg.setSpread(280);
    egg.setDirection({0, -0.8F});
    egg.setLifetime(20, 35);
    egg.setParticleShapeRect(5, 5);

    auto& blood = data.bloodParticles;
    blood.setEmissionShape(magique::Shape::RECT, 25, 25);
    blood.setGravity(0, 0.0F);
    blood.setSpread(360);
    blood.setVelocityRange(0.5, 1.0F);
    blood.setColorPool({Color{162, 38, 51, 255}, Color{246, 177, 122, 255}, Color{228, 59, 68, 255}});
    blood.setParticleShapeRect(3, 3);
    blood.setLifetime(15, 40);
}