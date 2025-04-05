#pragma once
#include "Enemy.h"
#include "Entity.h"

class Boss : public Enemy
{
private:
	std::string specialAbility;

public:
	Boss(const std::string& n, int h, const std::string& t, std::string ability) : Enemy(n, h, t), specialAbility(ability){}

	void displayInfo() const override {
		Entity::displayInfo();
		std::cout << "Special Ability: " << specialAbility << std::endl;
	}
};

