#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <string>

std::mutex monstersMutex;

class Entity {
protected:
    std::string name;
    int health;
    int attackPower;
    int defense;

public:
    Entity(const std::string& name, int hp, int atk, int def)
        : name(name), health(hp), attackPower(atk), defense(def) {}

    virtual ~Entity() {}

    bool isAlive() const {
        return health > 0;
    }

    void takeDamage(int amount) {
        int damage = amount - defense;
        if (damage < 1) damage = 1;
        health -= damage;
        if (health < 0) health = 0;
    }

    void attack(Entity& target) {
        target.takeDamage(attackPower);
    }

    std::string getName() const { return name; }
    int getHealth() const { return health; }

    void displayInfo() const {
        std::cout << name << " | HP: " << health << " | ATK: " << attackPower << " | DEF: " << defense << "\n";
    }
};

class Character : public Entity {
public:
    Character(const std::string& name, int hp, int atk, int def)
        : Entity(name, hp, atk, def) {}
};

class Monster : public Entity {
public:
    Monster(const std::string& name, int hp, int atk, int def)
        : Entity(name, hp, atk, def) {}
};

std::vector<Monster> monsters;
Character hero("рыцарь", 100, 20, 10);

void generateMonsters() {
    int count = 1;
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::lock_guard<std::mutex> lock(monstersMutex);
        monsters.emplace_back("КАЩЕЙ" + std::to_string(count++), 50, 15, 5);
        std::cout << ">> Новый монстр сгенерирован!\n";
    }
}

void fight() {
    while (hero.isAlive()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::lock_guard<std::mutex> lock(monstersMutex);

        if (!monsters.empty()) {
            Monster& current = monsters.front();

            if (current.isAlive()) {
                hero.attack(current);
                std::cout << hero.getName() << " атакует " << current.getName() << " (HP: " << current.getHealth() << ")\n";

                current.attack(hero);
                std::cout << current.getName() << " атакует " << hero.getName() << " (HP: " << hero.getHealth() << ")\n";
            }
            else {
                std::cout << current.getName() << " побежден!\n";
                monsters.erase(monsters.begin());
            }
        }
    }

    std::cout << "!!! Герой пал в бою.\n";
}

int main() {
    setlocale(LC_ALL, "RUS");

    std::thread monsterGenerator(generateMonsters);
    monsterGenerator.detach();

    std::thread battleThread(fight);
    battleThread.join(); 

    return 0;
}
