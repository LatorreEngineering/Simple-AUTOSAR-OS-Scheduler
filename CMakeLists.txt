cmake_minimum_required(VERSION 3.10)
project(SimpleAUTOSAROSScheduler)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_executable(led_toggle examples/led_toggle.cpp src/OS.cpp src/Task.cpp src/Event.cpp)
