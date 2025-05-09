#pragma once
#include <string>

class Character; // forward

class Monster {
protected:
    std::string name;
    int health, attack, defense;
public:
    Monster(const std::string& n, int h, int a, int d);
    virtual ~Monster() {}

    virtual void attackPlayer(Character& player) = 0;
    virtual void displayInfo() const;

    std::string getName() const;
    int getHealth() const;
    int getDefense() const;
    void takeDamage(int dmg);
};

class Goblin : public Monster {
public:
    Goblin();
    void attackPlayer(Character& player) override;
};

class Dragon : public Monster {
public:
    Dragon();
    void attackPlayer(Character& player) override;
};

class Skeleton : public Monster {
public:
    Skeleton();
    void attackPlayer(Character& player) override;
};
