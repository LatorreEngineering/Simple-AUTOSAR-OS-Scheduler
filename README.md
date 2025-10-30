# Simple-AUTOSAR-OS-Scheduler

A simplified AUTOSAR OS-like task scheduler implemented in C++.  
It demonstrates basic real-time scheduling concepts, including:

- Periodic tasks
- Alarms
- Event handling

## Features

- Define tasks with priorities
- Schedule periodic or one-shot tasks
- Set alarms to trigger tasks
- Wait for and signal events

## Example Use Case

Simulate toggling two LEDs at different frequencies or periodic sensor readings.

```cpp
#include "OS.hpp"
#include "Task.hpp"
#include "Event.hpp"

int main() {
    OS os;

    Task led1("LED1", 1000, [](){ 
        std::cout << "Toggle LED1\n"; 
    });

    Task led2("LED2", 500, [](){ 
        std::cout << "Toggle LED2\n"; 
    });

    os.addTask(led1);
    os.addTask(led2);

    os.start();
    return 0;
}
