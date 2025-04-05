#pragma once
#include "Entity.h";
class Enemy : public Entity {
private:
    std::string type; 

public:
    Enemy(const std::string& n, int h, const std::string& t)
        : Entity(n, h), type(t) {}

    void displayInfo() const override {
        Entity::displayInfo(); 
        std::cout << "Type: " << type << std::endl;
    }
};


