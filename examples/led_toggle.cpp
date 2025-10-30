#include "OS.hpp"
#include "Task.hpp"
#include <iostream>

int main() {
    OS os;

    Task led1("LED1", 1000, [](){ std::cout << "Toggle LED1\n"; });
    Task led2("LED2", 500, [](){ std::cout << "Toggle LED2\n"; });

    os.addTask(led1);
    os.addTask(led2);

    os.start();

    std::this_thread::sleep_for(std::chrono::seconds(5));
    os.stop();

    return 0;
}
