#pragma once
#include <vector>
#include <string>
#include <iostream>

template <typename T>
class Logger {
    std::vector<T> logs;

public:
    void log(const T& entry) {
        logs.push_back(entry);
        std::cout << "[LOG] " << entry << std::endl;
    }

    void showAll() const {
        for (const auto& entry : logs) {
            std::cout << entry << std::endl;
        }
    }
};
