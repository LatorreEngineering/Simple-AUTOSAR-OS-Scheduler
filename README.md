# Simple AUTOSAR OS-like Scheduler

A simplified AUTOSAR OS-like task scheduler implemented in C++. This project demonstrates basic real-time scheduling concepts such as task activation, preemption, alarms and simple resource handling — while keeping the implementation small and educational.

Status
- Language: C++
- License: MIT
- Default branch: main

Goals
- Provide a compact, readable implementation of a fixed-priority preemptive scheduler inspired by AUTOSAR OS concepts.
- Be easy to build and run on a host machine for experimentation and learning.
- Serve as a starting point for embedded ports and more complete OS features.

Non-goals / Limitations
- Not a full AUTOSAR OS implementation — many AUTOSAR features (full resource management, I/O, protection, services) are intentionally omitted.
- Not certified for safety-critical production use.
- Designed for education and prototyping; tradeoffs made for clarity where necessary.

Features
- Fixed-priority preemptive scheduling
- Task Control Blocks (TCBs) and ready queues
- Alarms / cyclic handlers
- Simple resource locking guidance (priority ceiling / inheritance not fully implemented unless documented)
- Host simulation mode (uses std::chrono for timing) for tests and demos

Quick Start (host)
1. Prerequisites
   - CMake >= 3.16
   - A C++17-capable compiler (gcc, clang, MSVC)
   - Optional: GoogleTest (or tests included as submodule), clang-format, clang-tidy

2. Build and run (example)
```bash
git clone https://github.com/LatorreEngineering/Simple-AUTOSAR-OS-Scheduler.git
cd Simple-AUTOSAR-OS-Scheduler
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -- -j
# run unit tests if built
ctest --output-on-failure
# run example binary (if provided)
./bin/scheduler_example
```

Illustrative usage example (API names are indicative; adjust to real headers)
```cpp
#include "os/scheduler.hpp"

int taskA() {
  // task body
  return 0;
}

int taskB() {
  // higher-priority task
  return 0;
}

int main() {
  OS::init();

  // Create tasks (id, priority, stack_size, entry)
  OS::create_task(1, /*priority=*/2, /*stack=*/1024, taskA);
  OS::create_task(2, /*priority=*/1, /*stack=*/1024, taskB);

  OS::activate_task(1);
  OS::activate_task(2);

  OS::start(); // starts scheduler loop (host simulation or target)
}
```

Recommended API (public functions you will find or want to provide)
- task_create / create_task
- activate_task
- terminate_task
- chain_task
- get_task_state
- wait_event / set_event
- alarm_create, alarm_start, alarm_cancel
- resource_acquire / resource_release (or document protocol)
- start / shutdown

Design & Architecture (summary)
- Kernel core: compact Task Control Blocks (TCB) holding id, state, priority, timing params.
- Ready queues: per-priority FIFO queues for deterministic wake ordering.
- Scheduler: fixed-priority preemptive. Tie-breaker: FIFO or configurable.
- Time management: tick-driven host simulation; alarms trigger activations/callbacks.
- Platform HAL: small abstraction for context switching, interrupt enable/disable, and time source. Host mode uses std::thread/std::chrono; embedded ports replace HAL.

Determinism & Safety guidance
- Avoid dynamic allocation in the scheduler core — prefer static pools for TCBs and queues.
- Keep interrupt-safe APIs: document which functions can be called from ISRs.
- If sharing resources from multiple tasks/ISRs, implement or document a resource protocol (priority ceiling or priority inheritance).
- Use atomic operations or critical sections for shared state.

Testing
- Unit tests for:
  - Priority preemption (high priority preempts low)
  - Multiple activations and termination behavior
  - Alarm expirations and periodic activations
  - Resource contention and priority inversion scenarios (if implemented)
- Integration tests: simulate time deterministically and assert schedule traces.
- Recommended: run with AddressSanitizer / UBSan in CI for host builds.

Building for embedded targets
- Provide a CMake toolchain file for cross-compilation.
- Implement a small HAL layer for your target (context switch, tick source, ISR entry).
- When porting: replace std::thread/time with target timers and implement stack/TCB layout accordingly.

Contribution
- Please open issues for bugs or feature requests.
- Prefer small, focused pull requests that include tests for new behavior.
- Follow code style (clang-format recommended). Add tests for any changed behavior.
- See CONTRIBUTING.md for details.

Repository layout (suggested)
- /src        — scheduler core, HAL stubs
- /examples   — small host-run examples
- /tests      — unit and integration tests
- /docs       — ARCHITECTURE.md, design notes
- CMakeLists.txt, LICENSE, README.md

License
This project is MIT licensed — see the LICENSE file.

Acknowledgements
This project is inspired by AUTOSAR OS concepts and intended for learning and prototyping.

Contact
Maintainer: LatorreEngineering (https://github.com/LatorreEngineering)
