#include <iostream>
#include <fstream>
#include <string>

class Person {
private:
    std::string name;
    int health;
    int level;

    const std::string filename = "person.txt";

public:
    Person(const std::string& name, int health, int level)
        : name(name), health(health), level(level) {
        saveToFile();
    }

    Person() {
        loadFromFile();
    }

    void saveToFile() const {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << name << '\n';
            outFile << health << '\n';
            outFile << level << '\n';
            outFile.close();
        }
    }

    void loadFromFile() {
        std::ifstream inFile(filename);
        if (inFile.is_open()) {
            std::getline(inFile, name);
            inFile >> health;
            inFile >> level;
            inFile.close();
        }
    }

    void display() const {
        std::cout << "Имя: " << name << std::endl;
        std::cout << "Здоровье: " << health << std::endl;
        std::cout << "Уровень: " << level << std::endl;
    }
};

int main() {
    setlocale(LC_ALL, "RUS");

    Person p1("Ансар", 100, 5);
    p1.display();

    Person p2;
    p2.display();

    return 0;
}