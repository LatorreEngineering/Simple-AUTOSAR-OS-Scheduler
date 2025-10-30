#pragma once
#include "Task.hpp"
#include "Event.hpp"
#include <functional>
#include <chrono>

class Alarm {
public:
    Alarm(Task* task, int delayMs, bool periodic = false);
    Alarm(Event* event, int delayMs, bool periodic = false);

    void start();
    void stop();

private:
    void runTask();
    void runEvent();

    Task* task = nullptr;
    Event* event = nullptr;
    int delayMs;
    bool periodic;
    std::atomic<bool> active{false};
    std::thread th;
};
