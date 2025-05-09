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
    std::cout << "������� ��� ��������� ";
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

    std::cout << "\n������� " << enemy->getName() << " ������!\n";
    enemy->displayInfo();

    while (enemy->getHealth() > 0 && player->getHealth() > 0) {
        player->attackEnemy(*enemy, logger);
        if (enemy->getHealth() <= 0) {
            std::cout << "�� ������� " << enemy->getName() << "!\n";
            player->gainExperience(50);
            player->addItem(Item("������ �� " + enemy->getName()));
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
        std::cout << "\n����:\n1. ���������\n2. ���������� ���������\n3. �������� ����������\n4. ���������\n5. ���������\n6. �����\n";
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
            std::cout << "�������� �����\n";
        }
    }
}
