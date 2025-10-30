# Architecture Overview — Simple AUTOSAR OS-like Scheduler

This document outlines recommended architecture elements:

- Kernel core
  - Task Control Block (TCB): id, priority, state, stack pointer (or simulated), timing params
  - Ready queues: per-priority FIFO
  - Scheduler: fixed-priority preemptive, tie-breaking policy
- Time management
  - Tick handler (host-simulated using std::chrono)
  - Alarms and cyclic handlers
- Resource management
  - Priority ceiling or inheritance protocol (recommended)
- API layers
  - Public API: task_create, activate_task, terminate_task, wait_event, set_event, get_state
  - Platform HAL: context switch, interrupt disable/enable, time source
- Safety & determinism
  - Prefer static allocation for TCBs, ready queues
  - No dynamic allocation inside the scheduler core
  - Clearly document ISR vs task-callable functions

Design rationale and trade-offs:
- Simplicity vs completeness: this project targets educational clarity; indicate which AUTOSAR features are intentionally omitted.
- Determinism: static sizing ensures predictable worst-case memory and timing.
