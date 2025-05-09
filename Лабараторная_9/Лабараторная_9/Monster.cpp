#include "Monster.h"
#include "Character.h"
#include <iostream>
#include <stdexcept>

Monster::Monster(const std::string& n, int h, int a, int d)
    : name(n), health(h), attack(a), defense(d) {}

void Monster::displayInfo() const {
    std::cout << "�������: " << name << ", ��: " << health
        << ", ����: " << attack << ", ������: " << defense << std::endl;
}

std::string Monster::getName() const { return name; }
int Monster::getHealth() const { return health; }
int Monster::getDefense() const { return defense; }

void Monster::takeDamage(int dmg) {
    health -= dmg;
    if (health < 0) throw std::runtime_error(name + " ������ ����");
}

Goblin::Goblin() : Monster("������", 30, 10, 5) {}
Dragon::Dragon() : Monster("������", 100, 25, 15) {}
Skeleton::Skeleton() : Monster("�����", 40, 12, 6) {}

void Goblin::attackPlayer(Character& player) {
    int dmg = attack - 3;
    if (dmg < 0) dmg = 0;
    std::cout << name << " �������� ������ �� " << dmg << " ��!" << std::endl;
    player.takeDamage(dmg);
}

void Dragon::attackPlayer(Character& player) {
    int dmg = attack - 5;
    if (dmg < 0) dmg = 0;
    std::cout << name << " �������� �����, ����� ������� " << dmg << " �����!" << std::endl;
    player.takeDamage(dmg);
}

void Skeleton::attackPlayer(Character& player) {
    int dmg = attack - 2;
    if (dmg < 0) dmg = 0;
    std::cout << name << " ������ �����, ����� �������� " << dmg << " �����!" << std::endl;
    player.takeDamage(dmg);
}
