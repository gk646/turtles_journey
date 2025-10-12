#include "TurtleGame.h"
#include "magique/assets/AssetPacker.h"
#include "magique/core/Game.h"

int main()
{
    // magique::CompileAssetImage("../res");
    TurtleGame game{};
    return game.run();
}