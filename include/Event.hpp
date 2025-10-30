#pragma once
#include <condition_variable>
#include <mutex>

class Event {
public:
    void wait();
    void signal();
private:
    std::mutex mtx;
    std::condition_variable cv;
    bool flag = false;
};
