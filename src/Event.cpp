#include "Event.hpp"

void Event::wait() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this]() { return flag; });
    flag = false;
}

void Event::signal() {
    std::lock_guard<std::mutex> lock(mtx);
    flag = true;
    cv.notify_one();
}
