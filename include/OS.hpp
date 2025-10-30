#pragma once
#include "Task.hpp"
#include <vector>
#include <thread>
#include <atomic>

class OS {
public:
    void addTask(Task& task);
    void start();
    void stop();

private:
    std::vector<Task*> tasks;
    std::vector<std::thread> threads;
    std::atomic<bool> running{false};
};
