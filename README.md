# Arduino FreeRTOS LED Blinking – Concept Demonstration

This project demonstrates a variety of **FreeRTOS** concepts using an Arduino-based **LED blinking setup**. Each concept is implemented in code through different task interactions, control mechanisms, and communication patterns.

---

## ✅ Development Covered

### 1. **Blocking Task using `vTaskDelay()`**
- Allows a task to sleep for a set period without blocking the scheduler.
- Used to blink an LED periodically in a non-blocking way.

### 2. **Mailbox using Queue (1:1 Communication)**
- A queue of length 1 used to pass messages (e.g. blink interval) between a sender and a receiver task.

### 3. **Producer-Consumer Pattern**
- One task (producer) generates data and places it into a queue.
- Another task (consumer) reads from the queue and acts (e.g., toggles LED).

### 4. **Queue Read/Write**
- Demonstrates writing multiple items to a queue and reading them in sequence.
- Used to buffer LED state changes or blink intervals.

### 5. **Sender-Receiver Queue**
- A classic communication pattern where one or more sender tasks pass data to a receiver task via a shared queue.

### 6. **Single Producer, Multiple Consumers**
- One producer task sends messages.
- Multiple consumer tasks read from individual or shared queues and act based on the message content.

### 7. **Task Suspension (`vTaskSuspend`)**
- A task can be suspended either by itself or by another task.
- Demonstrated by pausing an LED blinking task temporarily.

### 8. **Task Resumption (`vTaskResume`)**
- A previously suspended task is resumed and continues execution from where it left off.

### 9. **Self-Suspending Task**
- A task calls `vTaskSuspend(NULL)` to suspend itself under certain conditions (e.g. after N blinks).

### 10. **Task Instance / Handle**
- Tasks are created with handles, which are used for runtime control (e.g., suspend, resume, priority change).

### 11. **Task Switching**
- Implicit context switching between multiple tasks using FreeRTOS’s scheduler and cooperative multitasking.

### 12. **Changing Task Priority**
- Tasks can change their priority dynamically using `vTaskPrioritySet()` to control which task gets more CPU time.

### 13. **Getting Task Priority**
- `uxTaskPriorityGet()` is used to read the priority of any task, useful for diagnostics and dynamic behavior.

### 14. **Profiling with LED or Serial**
- Simple task profiling is done by toggling an LED or logging start/end of task execution to observe execution time or order.

---

## 🔧 Tools & Platform

- **Board**: Arduino UNO / Nano / Mega
- **RTOS**: [FreeRTOS](https://freertos.org)
- **Language**: C++ (Arduino Sketch)
- **Communication**: Queues, Task Handles
- **IDE**: Arduino IDE / PlatformIO (VS Code)

---

## 🎯 Development Outcome

By experimenting with these tasking and communication mechanisms, you will:
- Understand multitasking on microcontrollers.
- Learn non-blocking programming techniques.
- Master inter-task communication using queues.
- Dynamically manage task behavior and system responsiveness.

---

## 🧠 Recommended Next Steps

- Try mutexes and binary semaphores.
- Implement periodic software timers.
- Expand to UART or sensor data sharing between tasks.

---

## 📜 License

MIT License © Ankit Nath

---
