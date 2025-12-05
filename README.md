# 🧑‍💻 Philosopher - Concurrency & Deadlock Prevention

| Attribute | Description |
| :--- | :--- |
| **Project Goal** | Solve the classical dining philosophers problem using multithreading. |
| **Language** | C (Mandatory). |
| **Technical Focus** | POSIX Threads (pthreads), Mutexes, Concurrency, Deadlock & Race Condition Prevention. |
| **Objective** | Ensure all philosophers eat and no philosopher starves (livelock). |

## 🎯 Project Overview

This project simulates the **Dining Philosophers Problem**, a classic synchronisation problem in concurrent programming. The primary objective is to manage the shared resources (forks) among multiple competing processes (philosophers) to ensure smooth execution without entering a **deadlock** or **starvation** state.

### 1. The Simulation Model

The simulation runs under specific parameters defined by command-line arguments:

* **Number of Philosophers:** (Also equals the number of forks).
* **Time to Die:** The maximum time a philosopher can wait before dying of hunger.
* **Time to Eat:** The time taken for a philosopher to eat.
* **Time to Sleep:** The time taken for a philosopher to sleep.
* **[Optional] Number of Times Each Philosopher Must Eat:** If defined, the simulation stops when all philosophers meet this goal.

### 2. Philosopher States

Each philosopher must transition cleanly between three fundamental states, with accurate timestamp logging:
* **THINKING**
* **HUNGRY** (Waiting for forks)
* **EATING** (Holding two forks)
* **SLEEPING**
* **DEATH** (If time to die is reached)

## 💻 Technical Details & Challenges

1.  **Thread Management:** Creation and synchronization of threads (one thread per philosopher) using the **POSIX threads (pthreads)** library.
2.  **Resource Synchronization:** Implementation of **mutexes** to protect shared data and critical sections (especially the forks) from race conditions.
3.  **Deadlock Prevention:** The core technical challenge is designing the fork-acquisition logic (e.g., ordering, asymmetric acquisition) to guarantee that the simulation **never** deadlocks (where all philosophers are holding one fork and waiting for the other).
4.  **Time Management:** Accurate time tracking using microsecond precision to control the simulation duration and determine philosopher death.

## 🛠️ How to Run

1.  **Compilation:**
    ```bash
    make
    ```
2.  **Execution:**
    ```bash
    ./philo <num_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [num_must_eat]
    ```
    *Example:* `./philo 5 800 200 200 5` (5 philosophers, 5 meals each, simulating death if wait > 800ms)
