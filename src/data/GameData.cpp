#include "data/GameData.h"

GameData GAME_DATA{};

GameData& GetGameData() { return GAME_DATA; }