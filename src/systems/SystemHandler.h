#ifndef TURTLES_JOURNEY_RENDERSYSTEM_H
#define TURTLES_JOURNEY_RENDERSYSTEM_H

#include <vector>

struct GameSystem
{
    virtual ~GameSystem() = default;
    virtual void update() {}
    virtual void draw() {}
};

struct GameSystemHandler final
{
    void draw()
    {
        for (auto system : systems)
        {
            system->draw();
        }
    }

    void update()
    {
        for (auto system : systems)
        {
            system->update();
        }
    }

    void addSystem(GameSystem* system) { systems.push_back(system); }

private:
    std::vector<GameSystem*> systems;
};

struct BeachTurtleSystem final : GameSystem
{
    void update() override;
    void draw() override;
};

struct OverlaySystem final : GameSystem
{
    void update() override;
    void draw() override;
};

struct TextureSystem final : GameSystem
{
    void update() override;
    void draw() override;
};

struct AnimSystem final : GameSystem
{
    void update() override;
    void draw() override;
};

#endif // TURTLES_JOURNEY_RENDERSYSTEM_H