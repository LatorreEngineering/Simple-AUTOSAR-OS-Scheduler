#include "Alarm.hpp"
#include <thread>

Alarm::Alarm(Task* t, int delayMs, bool periodic)
    : task(t), delayMs(delayMs), periodic(periodic) {}

Alarm::Alarm(Event* e, int delayMs, bool periodic)
    : event(e), delayMs(delayMs), periodic(periodic) {}

void Alarm::start() {
    active = true;
    th = std::thread([this]() {
        do {
            std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
            if (!active) break;
            if (task) runTask();
            if (event) runEvent();
        } while(periodic && active);
    });
}

void Alarm::stop() {
    active = false;
    if (th.joinable()) th.join();
}

void Alarm::runTask() {
    if(task) task->run();
}

void Alarm::runEvent() {
    if(event) event->signal();
}
