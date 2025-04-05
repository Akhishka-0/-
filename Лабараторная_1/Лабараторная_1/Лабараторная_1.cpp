#include <iostream>
#include "Character.cpp"

int main()
{
    Character hero("Hero", 100, 20, 10);
    Character monster("Goblin", 50, 15, 5);
    
    hero.displayInfo();
    monster.displayInfo();

    // Герой атакует монстра
    hero.attackEnemy(monster);
    monster.attackEnemy(hero);

    hero.takeDamage(150);

    hero.displayInfo();
    monster.displayInfo();    
}
