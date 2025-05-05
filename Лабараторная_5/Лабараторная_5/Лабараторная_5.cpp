#include <iostream>
#include <queue>
#include <string>

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
        if (!data.empty()) {
            data.erase(data.begin());
        }
    }

    void DisplayAll() const {
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
    queInt.push(1);
    queInt.push(223);
    queInt.DisplayAll();
    queInt.pop();
    queInt.DisplayAll();

    Queue<std::string> queString;
    queString.push("УАЫ");
    queString.push("ФУАШЩ");
    queString.DisplayAll();
    queString.pop();
    queString.DisplayAll();

    return 0;

    
}
