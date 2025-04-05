#pragma once
#include "Entity.h"
class Player : Entity
{
private:
	int experience;

public:
	Player(const std::string n, int h, int exp) : Entity(n, h), experience(exp) {}

	void displayInfo() const override {
		Entity::displayInfo();
		std::cout << "Experience: " << experience << std::endl;
	}

};

