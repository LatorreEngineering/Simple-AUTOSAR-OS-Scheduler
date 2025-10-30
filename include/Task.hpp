#pragma once
#include <string>
#include <functional>

class Task {
public:
    Task(const std::string& name, int periodMs, std::function<void()> func);

    void run();
    int getPeriod() const;
    std::string getName() const;

private:
    std::string name;
    int periodMs;
    std::function<void()> taskFunc;
};
