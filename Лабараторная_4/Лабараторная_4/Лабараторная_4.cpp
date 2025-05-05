#include <iostream>
#include <memory>
#include <string>

class Inventory {
private:
    std::unique_ptr<std::string[]> items;
    size_t capacity;
    size_t count;

public:
    Inventory(size_t cap) : capacity(cap), count(0) {
        items = std::make_unique<std::string[]>(capacity);
    }

    void AddItem(const std::string& item) {
        if (count < capacity) {
            items[count++] = item;
        }

    }

    void DisplayInventory() const {
        std::cout << "Инвентарь\n";
        for (size_t i = 0; i < count; ++i) {
            std::cout << "- " << items[i] << std::endl;
        }
    }
};

int main() {
    Inventory inv(3);  

    inv.AddItem("Меч");
    inv.AddItem("Лук");
    inv.AddItem("АК-47");


    inv.DisplayInventory();

    return 0;
}
