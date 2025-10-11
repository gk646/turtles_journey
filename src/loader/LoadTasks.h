#ifndef TURTLES_JOURNEY_LOADTASKS_H
#define TURTLES_JOURNEY_LOADTASKS_H

#include "magique/core/Types.h"

struct SettingsLoader final : magique::ITask<magique::AssetContainer>
{
    void execute(magique::AssetContainer& res) override;
};

struct TextureLoader final : magique::ITask<magique::AssetContainer>
{
    void execute(magique::AssetContainer& res) override;
};

struct EntityLoader final : magique::ITask<magique::AssetContainer>
{
    void execute(magique::AssetContainer& res) override;
};
struct UILoader final : magique::ITask<magique::AssetContainer>
{
    void execute(magique::AssetContainer& res) override;
};

struct ParticleLoader final : magique::ITask<magique::AssetContainer>
{
    void execute(magique::AssetContainer& res) override;
};


#endif // TURTLES_JOURNEY_LOADTASKS_H