#pragma once
#include "Character.h"
#include "Monster.h"
#include "Inventory.h"
#include "Logger.h"
#include <memory>
#include <vector>

class Game {
private:
    std::unique_ptr<Character> player;
    std::vector<std::unique_ptr<Monster>> monsters;
    Logger<std::string> logger;

public:
    Game();
    void start();
    void createPlayer();
    void battle();
    void gameLoop();
};
