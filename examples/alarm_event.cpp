#include "OS.hpp"
#include "Task.hpp"
#include "Event.hpp"
#include "Alarm.hpp"
#include <iostream>

int main() {
    OS os;

    Event event;

    Task led1("LED1", 0, [&event](){ 
        std::cout << "LED1 toggled by Event\n"; 
        event.wait(); // Wait for next trigger
    });

    Task sensor("Sensor", 0, [](){ 
        std::cout << "Sensor reading taken\n"; 
    });

    os.addTask(led1);
    os.addTask(sensor);

    // Alarm triggers LED1 event every 1s
    Alarm ledAlarm(&event, 1000, true);

    // Alarm triggers sensor reading every 2s
    Alarm sensorAlarm(&sensor, 2000, true);

    ledAlarm.start();
    sensorAlarm.start();
    os.start();

    std::this_thread::sleep_for(std::chrono::seconds(10));

    ledAlarm.stop();
    sensorAlarm.stop();
    os.stop();

    return 0;
}
