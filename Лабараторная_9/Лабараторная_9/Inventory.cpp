#include "Inventory.h"

Item::Item(const std::string& n) : name(n) {}

std::string Item::getName() const { return name; }

void Inventory::addItem(const Item& item) {
    items.push_back(item);
}

void Inventory::removeItem(const std::string& itemName) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getName() == itemName) {
            items.erase(it);
            return;
        }
    }
}

void Inventory::showInventory() const {
    std::cout << "Инвентарь:\n";
    for (const auto& item : items) {
        std::cout << "- " << item.getName() << std::endl;
    }
}
