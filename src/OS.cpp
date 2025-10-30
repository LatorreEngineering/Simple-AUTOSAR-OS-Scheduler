#include "OS.hpp"
#include <chrono>

void OS::addTask(Task& task) {
    tasks.push_back(&task);
}

void OS::start() {
    running = true;
    for(auto task : tasks) {
        threads.emplace_back([this, task]() {
            while(running) {
                task->run();
                std::this_thread::sleep_for(std::chrono::milliseconds(task->getPeriod()));
            }
        });
    }
}

void OS::stop() {
    running = false;
    for(auto &t : threads) {
        if(t.joinable())
            t.join();
    }
}
