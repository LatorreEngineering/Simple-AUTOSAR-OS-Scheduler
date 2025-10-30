#include "Task.hpp"

Task::Task(const std::string& name, int periodMs, std::function<void()> func)
    : name(name), periodMs(periodMs), taskFunc(func) {}

void Task::run() {
    taskFunc();
}

int Task::getPeriod() const {
    return periodMs;
}

std::string Task::getName() const {
    return name;
}
