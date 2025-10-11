#include "data/GameData.h"
#include "loader/LoadTasks.h"

void ParticleLoader::execute(magique::AssetContainer& res)
{
    auto& data = GetGameData();

    auto& egg = data.eggParticles;
    egg.setEmissionShape(magique::Shape::RECT, 42, 52);
    egg.setGravity(0, -1.0F);
    egg.setColorPool({data.colors.textHighlight, data.colors.text, data.colors.textPassive});
    egg.setSpread(280);
    egg.setDirection({0, -0.8F});
    egg.setLifetime(20, 35);
    egg.setParticleShapeRect(3, 3);

    auto& blood = data.bloodParticles;
    blood.setEmissionShape(magique::Shape::RECT, 25, 25);
    blood.setGravity(0, 0.0F);
    blood.setSpread(360);
    blood.setVelocityRange(0.5, 1.0F);
    blood.setColorPool({Color{162, 38, 51, 255}, Color{246, 177, 122, 255}, Color{228, 59, 68, 255}});
    blood.setParticleShapeRect(2, 2);
    blood.setLifetime(15, 40);

    auto& yum = data.yumParticles;
    yum.setEmissionShape(magique::Shape::RECT, 25, 25);
    yum.setGravity(0, 0.0F);
    yum.setSpread(360);
    yum.setVelocityRange(0.5, 1.0F);
    yum.setColorPool({Color{99, 199, 77, 255}, Color{62, 137, 72, 255}, Color{38, 92, 66, 255}});
    yum.setLifetime(20, 45);
    yum.setParticleShapeRect(2, 2);

    auto& water = data.waterParticles;
    water.setEmissionShape(magique::Shape::RECT, 50, 70);
    water.setGravity(0, -1.0F);
    water.setLifetime(100, 200);
    water.setColorPool({data.colors.textHighlight, data.colors.text, Color{44, 232, 245, 255}});
    water.setParticleShapeRect(1, 1);
    water.setDirection({0, -1.0F});
    water.setSpread(20);
}