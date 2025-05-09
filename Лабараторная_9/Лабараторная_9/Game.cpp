#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Game::start() {
    createPlayer();
    gameLoop();
}

void Game::createPlayer() {
    std::string name;
    std::cout << "Введите имя персонажа ";
    std::cin >> name;
    player = std::make_unique<Character>(name, 100, 20, 10);
    player->displayInfo();
}

void Game::battle() {
    int monsterType = std::rand() % 3;
    std::unique_ptr<Monster> enemy;

    if (monsterType == 0) enemy = std::make_unique<Goblin>();
    else if (monsterType == 1) enemy = std::make_unique<Dragon>();
    else enemy = std::make_unique<Skeleton>();

    std::cout << "\nМонстор " << enemy->getName() << " создан!\n";
    enemy->displayInfo();

    while (enemy->getHealth() > 0 && player->getHealth() > 0) {
        player->attackEnemy(*enemy, logger);
        if (enemy->getHealth() <= 0) {
            std::cout << "Ты победил " << enemy->getName() << "!\n";
            player->gainExperience(50);
            player->addItem(Item("Добыча из " + enemy->getName()));
            break;
        }
        try {
            enemy->attackPlayer(*player);
        }
        catch (std::runtime_error& e) {
            logger.log(e.what());
            std::cout << e.what() << std::endl;
            break;
        }
    }
}

void Game::gameLoop() {
    bool playing = true;
    while (playing) {
        std::cout << "\nМеню:\n1. Атаковать\n2. Посмотреть инвентарь\n3. Показать информацию\n4. Сохранить\n5. Загрузить\n6. Выйти\n";
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            battle();
            break;
        case 2:
            player->showInventory();
            break;
        case 3:
            player->displayInfo();
            break;
        case 4:
            player->save("savefile.txt");
            break;
        case 5:
            player->load("savefile.txt");
            break;
        case 6:
            playing = false;
            break;
        default:
            std::cout << "Неверный вывод\n";
        }
    }
}
