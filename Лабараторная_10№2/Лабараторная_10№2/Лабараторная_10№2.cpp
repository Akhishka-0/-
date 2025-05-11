#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <sstream>
#include <limits>

#pragma region Базовый класс пользователя
class User {
protected:
    std::string name;
    int id;
    int accessLevel;

public:
    User(const std::string& name, int id, int accessLevel)
        : name(name), id(id), accessLevel(accessLevel) {
        if (name.empty()) {
            throw std::invalid_argument("Имя пользователя не может быть пустым");
        }
        if (accessLevel < 0) {
            throw std::invalid_argument("Уровень доступа не может быть отрицательным");
        }
    }

    virtual ~User() {}

    std::string getName() const { return name; }
    int getId() const { return id; }
    int getAccessLevel() const { return accessLevel; }

    void setName(const std::string& newName) {
        if (newName.empty()) {
            throw std::invalid_argument("Имя пользователя не может быть пустым");
        }
        name = newName;
    }

    void setAccessLevel(int level) {
        if (level < 0) {
            throw std::invalid_argument("Уровень доступа не может быть отрицательным");
        }
        accessLevel = level;
    }

    virtual void displayInfo() const {
        std::cout << "Имя: " << name << ", ID: " << id
            << ", Уровень доступа: " << accessLevel;
    }

    virtual std::string toFileString() const {
        return "User," + name + "," + std::to_string(id) + "," + std::to_string(accessLevel);
    }
};
#pragma endregion

#pragma region Класс студента
class Student : public User {
private:
    std::string group;

public:
    Student(const std::string& name, int id, int accessLevel, const std::string& group)
        : User(name, id, accessLevel), group(group) {
        if (group.empty()) {
            throw std::invalid_argument("Группа не может быть пустой");
        }
    }

    std::string getGroup() const { return group; }
    void setGroup(const std::string& newGroup) {
        if (newGroup.empty()) {
            throw std::invalid_argument("Группа не может быть пустой");
        }
        group = newGroup;
    }

    void displayInfo() const override {
        User::displayInfo();
        std::cout << ", Группа: " << group << " (Студент)";
    }

    std::string toFileString() const override {
        return "Student," + name + "," + std::to_string(id) + ","
            + std::to_string(accessLevel) + "," + group;
    }
};
#pragma endregion

#pragma region Класс преподавателя
class Teacher : public User {
private:
    std::string department;

public:
    Teacher(const std::string& name, int id, int accessLevel, const std::string& department)
        : User(name, id, accessLevel), department(department) {
        if (department.empty()) {
            throw std::invalid_argument("Кафедра не может быть пустой");
        }
    }

    std::string getDepartment() const { return department; }
    void setDepartment(const std::string& newDepartment) {
        if (newDepartment.empty()) {
            throw std::invalid_argument("Кафедра не может быть пустой");
        }
        department = newDepartment;
    }

    void displayInfo() const override {
        User::displayInfo();
        std::cout << ", Кафедра: " << department << " (Преподаватель)";
    }

    std::string toFileString() const override {
        return "Teacher," + name + "," + std::to_string(id) + ","
            + std::to_string(accessLevel) + "," + department;
    }
};
#pragma endregion

#pragma region Класс Администратора
class Administrator : public User {
private:
    std::string position;

public:
    Administrator(const std::string& name, int id, int accessLevel, const std::string& position)
        : User(name, id, accessLevel), position(position) {
        if (position.empty()) {
            throw std::invalid_argument("Должность не может быть пустой");
        }
    }

    std::string getPosition() const { return position; }
    void setPosition(const std::string& newPosition) {
        if (newPosition.empty()) {
            throw std::invalid_argument("Должность не может быть пустой");
        }
        position = newPosition;
    }

    void displayInfo() const override {
        User::displayInfo();
        std::cout << ", Должность: " << position << " (Администратор)";
    }

    std::string toFileString() const override {
        return "Administrator," + name + "," + std::to_string(id) + ","
            + std::to_string(accessLevel) + "," + position;
    }
};
#pragma endregion

#pragma region Ресурс
class Resource {
private:
    std::string name;
    int requiredAccessLevel;

public:
    Resource(const std::string& name, int requiredAccessLevel)
        : name(name), requiredAccessLevel(requiredAccessLevel) {
        if (name.empty()) {
            throw std::invalid_argument("Название ресурса не может быть пустым");
        }
        if (requiredAccessLevel < 0) {
            throw std::invalid_argument("Требуемый уровень доступа не может быть отрицательным");
        }
    }

    std::string getName() const { return name; }
    int getRequiredAccessLevel() const { return requiredAccessLevel; }

    void setName(const std::string& newName) {
        if (newName.empty()) {
            throw std::invalid_argument("Название ресурса не может быть пустым");
        }
        name = newName;
    }

    void setRequiredAccessLevel(int level) {
        if (level < 0) {
            throw std::invalid_argument("Требуемый уровень доступа не может быть отрицательным");
        }
        requiredAccessLevel = level;
    }

    bool checkAccess(const User& user) const {
        return user.getAccessLevel() >= requiredAccessLevel;
    }

    std::string toFileString() const {
        return name + "," + std::to_string(requiredAccessLevel);
    }
};
#pragma endregion

#pragma region Класс для храниения и вывода ресурсов
template<typename T>
class AccessControlSystem {
private:
    std::vector<std::unique_ptr<User>> users;
    std::vector<T> resources;
    const std::string filename = "university_access_system.txt";

public:
    void addUser(std::unique_ptr<User> user) {
        users.push_back(std::move(user));
        saveToFile();
    }

    void addResource(const T& resource) {
        resources.push_back(resource);
        saveToFile();
    }

    bool checkAccess(int userId, const std::string& resourceName) const {
        auto userIt = std::find_if(users.begin(), users.end(),
            [userId](const std::unique_ptr<User>& u) { return u->getId() == userId; });

        auto resourceIt = std::find_if(resources.begin(), resources.end(),
            [resourceName](const T& r) { return r.getName() == resourceName; });

        if (userIt == users.end() || resourceIt == resources.end()) {
            return false;
        }

        return resourceIt->checkAccess(**userIt);
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user->displayInfo();
            std::cout << std::endl;
        }
    }

    void displayAllResources() const {
        for (const auto& resource : resources) {
            std::cout << "Ресурс: " << resource.getName()
                << ", Требуемый уровень доступа: "
                << resource.getRequiredAccessLevel() << std::endl;
        }
    }

    const User* findUserByName(const std::string& name) const {
        auto it = std::find_if(users.begin(), users.end(),
            [name](const std::unique_ptr<User>& u) { return u->getName() == name; });
        return it != users.end() ? it->get() : nullptr;
    }

    const User* findUserById(int id) const {
        auto it = std::find_if(users.begin(), users.end(),
            [id](const std::unique_ptr<User>& u) { return u->getId() == id; });
        return it != users.end() ? it->get() : nullptr;
    }

    void sortUsersByAccessLevel() {
        std::sort(users.begin(), users.end(),
            [](const std::unique_ptr<User>& a, const std::unique_ptr<User>& b) {
                return a->getAccessLevel() < b->getAccessLevel();
            });
        saveToFile();
    }

    void saveToFile() const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для записи");
        }

        for (const auto& user : users) {
            file << user->toFileString() << std::endl;
        }

        file << "---Ресурс---" << std::endl;

        for (const auto& resource : resources) {
            file << resource.toFileString() << std::endl;
        }

        file.close();
    }

    void loadFromFile() {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return;
        }

        users.clear();
        resources.clear();

        std::string line;
        bool readingResources = false;

        while (std::getline(file, line)) {
            if (line.empty()) continue;

            if (line == "---RESOURCES---") {
                readingResources = true;
                continue;
            }

            if (!readingResources) {
                std::istringstream iss(line);
                std::string type;
                std::getline(iss, type, ',');

                std::string name;
                std::getline(iss, name, ',');

                std::string idStr;
                std::getline(iss, idStr, ',');
                int id = std::stoi(idStr);

                std::string accessStr;
                std::getline(iss, accessStr, ',');
                int accessLevel = std::stoi(accessStr);

                if (type == "Student") {
                    std::string group;
                    std::getline(iss, group);
                    users.push_back(std::make_unique<Student>(name, id, accessLevel, group));
                }
                else if (type == "Teacher") {
                    std::string department;
                    std::getline(iss, department);
                    users.push_back(std::make_unique<Teacher>(name, id, accessLevel, department));
                }
                else if (type == "Administrator") {
                    std::string position;
                    std::getline(iss, position);
                    users.push_back(std::make_unique<Administrator>(name, id, accessLevel, position));
                }
                else {
                    users.push_back(std::make_unique<User>(name, id, accessLevel));
                }
            }
            else {
                std::istringstream iss(line);
                std::string name;
                std::getline(iss, name, ',');

                std::string accessStr;
                std::getline(iss, accessStr);
                int accessLevel = std::stoi(accessStr);

                resources.emplace_back(name, accessLevel);
            }
        }

        file.close();
    }
};
#pragma endregion

#pragma region Функции для ввода данных
int getIntInput(const std::string& prompt, int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max()) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min && value <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка ввода. Пожалуйста, введите целое число между "
            << min << " и " << max << std::endl;
    }
}
#pragma endregion

std::string getStringInput(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        if (!value.empty()) {
            return value;
        }
        std::cout << "Ошибка ввода. Поле не может быть пустым." << std::endl;
    }
}

#pragma region Меню Добавление пользователя
void addUserMenu(AccessControlSystem<Resource>& system) {
    std::cout << "\nДобавление нового пользователя:\n";
    std::cout << "1. Студент\n";
    std::cout << "2. Преподаватель\n";
    std::cout << "3. Администратор\n";
    std::cout << "0. Назад\n";

    int choice = getIntInput("Выберите тип пользователя: ", 0, 3);
    if (choice == 0) return;

    std::string name = getStringInput("Введите имя пользователя: ");
    int id = getIntInput("Введите ID пользователя: ");
    int accessLevel = getIntInput("Введите уровень доступа (0-10): ", 0, 10);

    try {
        switch (choice) {
        case 1: {
            std::string group = getStringInput("Введите группу студента: ");
            system.addUser(std::make_unique<Student>(name, id, accessLevel, group));
            std::cout << "Студент успешно добавлен!\n";
            break;
        }
        case 2: {
            std::string department = getStringInput("Введите кафедру преподавателя: ");
            system.addUser(std::make_unique<Teacher>(name, id, accessLevel, department));
            std::cout << "Преподаватель успешно добавлен!\n";
            break;
        }
        case 3: {
            std::string position = getStringInput("Введите должность администратора: ");
            system.addUser(std::make_unique<Administrator>(name, id, accessLevel, position));
            std::cout << "Администратор успешно добавлен!\n";
            break;
        }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка при добавлении пользователя: " << e.what() << std::endl;
    }
}
#pragma endregion

#pragma region Добавление нового ресурса
void addResourceMenu(AccessControlSystem<Resource>& system) {
    std::cout << "\nДобавление нового ресурса:\n";
    std::string name = getStringInput("Введите название ресурса: ");
    int requiredAccess = getIntInput("Введите требуемый уровень доступа (0-10): ", 0, 10);

    try {
        system.addResource(Resource(name, requiredAccess));
        std::cout << "Ресурс успешно добавлен!\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка при добавлении ресурса: " << e.what() << std::endl;
    }
}
#pragma endregion

#pragma region Проверка доступа к ресурсу
void checkAccessMenu(AccessControlSystem<Resource>& system) {
    std::cout << "\nПроверка доступа:\n";

    system.displayAllUsers();
    int userId = getIntInput("Введите ID пользователя для проверки: ");

    system.displayAllResources();
    std::string resourceName = getStringInput("Введите название ресурса: ");

    if (system.checkAccess(userId, resourceName)) {
        std::cout << "Доступ РАЗРЕШЕН!\n";
    }
    else {
        std::cout << "Доступ ЗАПРЕЩЕН!\n";
    }
}
#pragma endregion

#pragma region Главное Меню
void mainMenu() {
    AccessControlSystem<Resource> system;
    system.loadFromFile();

    while (true) {
        std::cout << "\nСистема контроля доступа университета\n";
        std::cout << "1. Добавить пользователя\n";
        std::cout << "2. Добавить ресурс\n";
        std::cout << "3. Проверить доступ\n";
        std::cout << "4. Показать всех пользователей\n";
        std::cout << "5. Показать все ресурсы\n";
        std::cout << "0. Выход\n";

        int choice = getIntInput("Выберите действие: ", 0, 5);

        try {
            switch (choice) {
            case 1:
                addUserMenu(system);
                break;
            case 2:
                addResourceMenu(system);
                break;
            case 3:
                checkAccessMenu(system);
                break;
            case 4:
                std::cout << "\nСписок всех пользователей:\n";
                system.displayAllUsers();
                break;
            case 5:
                std::cout << "\nСписок всех ресурсов:\n";
                system.displayAllResources();
                break;
            case 0:
                std::cout << "Сохранение данных и выход...\n";
                system.saveToFile();
                return;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }
    }
}
#pragma endregion

int main() {
    setlocale(LC_ALL, "RUS");
    try {
        mainMenu();
    }
    catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}