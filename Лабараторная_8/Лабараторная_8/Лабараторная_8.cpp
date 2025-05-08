#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age;
    std::string email;
    std::string address; 

public:
    std::string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    std::string getEmail() const {
        return email;
    }

    std::string getAddress() const {
        return address;
    }

    void setName(const std::string& newName) {
        if (!newName.empty()) {
            name = newName;
        }
        else {
            std::cerr << "Ошибка: Имя не может быть пустым!" << std::endl;
        }
    }

    void setAge(int newAge) {
        if (newAge >= 0 && newAge <= 120) {
            age = newAge;
        }
        else {
            std::cerr << "Ошибка: Возраст должен быть от 0 до 120 лет!" << std::endl;
        }
    }

    void setEmail(const std::string& newEmail) {
        if (newEmail.find('@') != std::string::npos) {
            email = newEmail;
        }
        else {
            std::cerr << "Ошибка: Неверный формат электронной почты!" << std::endl;
        }
    }

    void setAddress(const std::string& newAddress) { 
        if (!newAddress.empty()) {
            address = newAddress;
        }
        else {
            std::cerr << "Ошибка: Адрес не может быть пустым!" << std::endl;
        }
    }

    void displayInfo() const {
        std::cout << "Name: " << name
            << ", Age: " << age
            << ", Email: " << email
            << ", Address: " << address << std::endl;
    }
};

int main() {
    setlocale(LC_ALL, "RUS");
    Person person;

    person.setName("Ансар Ш");
    person.setAge(25);
    person.setEmail("shihaliev@gmail.com");
    person.setAddress("Текучева 145");

    std::cout << "Имя: " << person.getName() << std::endl;
    std::cout << "Возраст: " << person.getAge() << std::endl;
    std::cout << "Почта: " << person.getEmail() << std::endl;
    std::cout << "Адрес: " << person.getAddress() << std::endl;

    std::cout << "\n-----------Неверные данные----------- \n" << std::endl;

    person.setName(""); 
    person.setAge(150); 
    person.setEmail("фшафвашш"); 
    person.setAddress(""); 

    person.displayInfo();

    return 0;
}
