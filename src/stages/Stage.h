#ifndef TURTLES_JOURNEY_SCENE_H
#define TURTLES_JOURNEY_SCENE_H

#include "fwd.h"
#include "magique/ecs/ECS.h"

struct Stage
{
    virtual ~Stage() = default;

    // Called once
    virtual void onStart() {}
    virtual void onEnd() { cleanEntities(); }

    virtual void update(TurtleGame& game, GameState gameState) {}
    virtual void draw(TurtleGame& game, GameState gameState) {}
    virtual void drawOnTop() {}
    void registerEntity(entt::entity e) { stageEntities.push_back(e); }
    void cleanEntities()
    {
        for (const auto e : stageEntities)
        {
            magique::DestroyEntity(e);
        }
    }

protected:
    std::vector<entt::entity> stageEntities;
};

struct Stage1Beach : Stage
{
    void onStart() override;
    void onEnd() override;

    void update(TurtleGame& game, GameState gameState) override;
    void draw(TurtleGame& game, GameState gameState) override;
};

struct Stage2Street : Stage
{
    void onStart() override;
    void onEnd() override;

    void update(TurtleGame& game, GameState gameState) override;
    void draw(TurtleGame& game, GameState gameState) override;
};

struct Stage3Ocean : Stage
{
    void onStart() override;
    void onEnd() override;

    void update(TurtleGame& game, GameState gameState) override;
    void draw(TurtleGame& game, GameState gameState) override;
    void drawOnTop() override;
};


#endif // TURTLES_JOURNEY_SCENE_H