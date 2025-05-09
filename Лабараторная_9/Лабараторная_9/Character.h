#pragma once
#include <string>
#include "Inventory.h"
#include "Monster.h"
#include "Logger.h"

class Character {
private:
    std::string name;
    int health;
    int attack;
    int defense;
    int level;
    int experience;
    Inventory inventory;

public:
    Character(const std::string& n, int h, int a, int d);

    void attackEnemy(Monster& enemy, Logger<std::string>& logger);
    void heal(int amount, Logger<std::string>& logger);
    void gainExperience(int exp);
    void displayInfo() const;
    void addItem(const Item& item);
    void showInventory() const;
    void takeDamage(int dmg);
    std::string getName() const;
    int getHealth() const;
    void save(const std::string& filename) const;
    void load(const std::string& filename);
};
