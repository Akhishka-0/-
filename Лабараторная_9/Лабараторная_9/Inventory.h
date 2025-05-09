#pragma once
#include <string>
#include <vector>
#include <iostream>

class Item {
    std::string name;
public:
    Item(const std::string& n);
    std::string getName() const;
};

class Inventory {
    std::vector<Item> items;
public:
    void addItem(const Item& item);
    void removeItem(const std::string& itemName);
    void showInventory() const;
};
