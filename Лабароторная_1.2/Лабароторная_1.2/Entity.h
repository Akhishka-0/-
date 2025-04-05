#pragma once
#include <iostream>;
#include <string>;


class Entity
{
protected:
    std::string name; 
    int health;      

public:
    Entity(const std::string& n, int h) : name(n), health(h) {}

    virtual void displayInfo() const {
        std::cout << "Name: " << name << ", HP: " << health << std::endl;
    }

    virtual ~Entity() {}


};


