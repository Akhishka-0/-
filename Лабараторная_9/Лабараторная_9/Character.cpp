#include "Character.h"
#include "Character.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

Character::Character(const std::string& n, int h, int a, int d)
    : name(n), health(h), attack(a), defense(d), level(1), experience(0) {}

void Character::attackEnemy(Monster& enemy, Logger<std::string>& logger) {
    int damage = attack - enemy.getDefense();
    if (damage < 0) damage = 0;
    logger.log(name + " ������� " + enemy.getName() + " � ������� " + std::to_string(damage) + " �����.");
    try {
        enemy.takeDamage(damage);
    }
    catch (std::runtime_error& e) {
        logger.log(e.what());
        std::cout << e.what() << std::endl;
    }
}

void Character::heal(int amount, Logger<std::string>& logger) {
    health += amount;
    if (health > 100) health = 100;
    logger.log(name + " ���������� �� " + std::to_string(amount) + " ��.");
    std::cout << name << "  " << amount << " ��!" << std::endl;
}

void Character::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        level++;
        experience -= 100;
        std::cout << name << " ����� �� ������ " << level << "!" << std::endl;
    }
}

void Character::displayInfo() const {
    std::cout << "���: " << name << ", ��: " << health
        << ", ����: " << attack << ", ������: " << defense
        << ", �������: " << level << ", ����: " << experience << std::endl;
}

void Character::addItem(const Item& item) {
    inventory.addItem(item);
}

void Character::showInventory() const {
    inventory.showInventory();
}

void Character::takeDamage(int dmg) {
    health -= dmg;
    if (health <= 0) throw std::runtime_error(name + " ����!");
}

std::string Character::getName() const { return name; }
int Character::getHealth() const { return health; }

void Character::save(const std::string& filename) const {
    std::ofstream file(filename);
    file << name << "\n" << health << "\n" << attack << "\n"
        << defense << "\n" << level << "\n" << experience << std::endl;
}

void Character::load(const std::string& filename) {
    std::ifstream file(filename);
    file >> name >> health >> attack >> defense >> level >> experience;
}
