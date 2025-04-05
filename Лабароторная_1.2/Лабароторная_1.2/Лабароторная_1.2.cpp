#include <iostream>
#include "Entity.cpp"


int main()
{

    Player hero("Hero", 100, 0);
    Enemy monster("Goblin", 50, "Goblin");

    hero.displayInfo();
    monster.displayInfo();


    return 0;

}

