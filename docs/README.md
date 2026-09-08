*This project has been created as part of the 42 curriculum by timtan.*

## Description
Philosophers is a C implementation of Edsger Dijkstra's classic Dining Philosophers problem, designed to explore concurrent programming, multithreading, and resource synchronization.

The project simulates a table of philosophers who endlessly alternate between eating, sleeping, and thinking. Because the philosophers share forks (represented by mutexes) and cannot communicate, the underlying architecture must meticulously manage resource allocation to prevent fatal concurrency issues: deadlocks (where the entire table freezes) and starvation (where a single philosopher dies due to a lack of CPU priority).

## Instructions
### Installation
Open your preferred terminal application and run this command.
```bash
git clone https://github.com/timmmtam/dining-philosophers.git philosophers && cd philosophers
```

### Compilation
Run the following command at the root of the repository to compile the executable file:
```bash
make
```

### Execution
The program takes 4 or 5 arguments, all formatted in milliseconds:
```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

- number_of_philosophers: The total amount of philosophers and forks on the table.

- time_to_die: Maximum time a philosopher can survive without starting a meal.

- time_to_eat: Time it takes to finish a meal (requires holding 2 forks).

- time_to_sleep: Time spent sleeping after a meal is completed.

- number_of_times_each_philosopher_must_eat: (Optional) If all philosophers eat at least this many times, the simulation cleanly halts.

## Resources
### Official Documentation & Articles
* [Apple Developer macOS pthread(3) Manual Page Reference](https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/pthread.3.html) -> used frequently as reference when coding
* [Deadlock Prevention](https://www.geeksforgeeks.org/operating-systems/deadlock-prevention/) -> to learn more about deadlocks

### Helpful Guides
* [CodeVault: Unix Threads in C](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2) -> for learning how to use pthread
* [Dining Philosophers Problem Explanation](https://www.youtube.com/watch?v=NbwbQQB7xNQ&t=92s) -> to understand the problem

### AI Usage
AI was used in these areas throughout the development of this project:
1. Researcher - used to find & consolidate information online.
1. Study guide - used to help understand important concepts while promoting problem solving
1. Judge - used to verify output
1. README helper - used in the making of this README
