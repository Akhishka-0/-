#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

// Шаблонный класс Queue
template <typename T>
class Queue {
private:
    std::vector<T> data;

public:
    void push(const T& item) {
        data.push_back(item);
    }

    void pop() {
        if (data.empty()) {
            throw std::out_of_range("Массив пуст");
        }
        data.erase(data.begin());
    }

    void DisplayInfo() const {
        std::cout << "Массив: ";
        for (const auto& item : data) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    setlocale(LC_ALL, "RUS");

    Queue<int> queInt;
    try {
        queInt.push(1);
        queInt.push(2);
        queInt.pop();
        queInt.pop();
        queInt.pop();
    }
    catch (const std::out_of_range& error) {
        std::cerr << "Ошибка ! " << error.what() << std::endl;
    }
}