*This project has been created as part of the 42 curriculum by moodeh.*
# Philosophers
## Description

The **Dining Philosophers** problem is a classic synchronization and concurrency challenge in computer science. This project implements a solution using threads and mutexes to simulate philosophers sitting at a round table, where they must eat, think, and sleep while sharing a limited number of forks.

The goal is to prevent deadlock and ensure that no philosopher starves while maintaining proper synchronization between threads. Each philosopher is represented by a thread, and each fork is protected by a mutex to prevent race conditions.

### Key Concepts
- **Multithreading**: Each philosopher runs in their own thread
- **Mutex synchronization**: Forks are protected by mutexes to prevent concurrent access
- **Deadlock prevention**: Philosophers acquire forks in a specific order to avoid circular waiting
- **Resource sharing**: Managing limited resources (forks) among competing threads

## Instructions

### Compilation
To compile the project, simply run:
```bash
make
```

This will generate the `philo` executable.

### Execution
Run the program with the following syntax:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Parameters:**
- `number_of_philosophers`: The number of philosophers and also the number of forks (1-200)
- `time_to_die`: Time in milliseconds - if a philosopher doesn't start eating within this time from their last meal, they die
- `time_to_eat`: Time in milliseconds it takes for a philosopher to eat
- `time_to_sleep`: Time in milliseconds a philosopher spends sleeping
- `[number_of_times_each_philosopher_must_eat]`: (Optional) If specified, the simulation stops when all philosophers have eaten at least this many times. If not specified, the simulation runs until a philosopher dies.

**Example:**
```bash
./philo 5 800 200 200
```
This creates 5 philosophers who die after 800ms without eating, take 200ms to eat, and sleep for 200ms.

```bash
./philo 5 800 200 200 7
```
Same as above, but the simulation stops when all philosophers have eaten 7 times.

### Output
The program outputs timestamped state changes for each philosopher:
- `timestamp_in_ms X has taken a fork`
- `timestamp_in_ms X is eating`
- `timestamp_in_ms X is sleeping`
- `timestamp_in_ms X is thinking`
- `timestamp_in_ms X died`

Where `X` is the philosopher ID and `timestamp_in_ms` is the current timestamp in milliseconds from the start of the simulation.

### Cleaning
To clean object files:
```bash
make clean
```

To remove all generated files including the executable:
```bash
make fclean
```

To recompile everything from scratch:
```bash
make re
```

## Resources

### Classic References
- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming](https://hpc-tutorials.llnl.gov/posix/)
- [Mutex Tutorial](https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/)
- [Mutexes and Condition Variables](https://www.man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html) - The official `man` pages are an invaluable 
- [Visualizing Processes with fork()](https://www.youtube.com/watch?v=cex9T-i_y7I) - A great YouTube video that visually explains how the `fork()` system 
- [Threads and `pthread` Introduction](https://www.youtube.com/watch?v=It0OFCbbTJE) - An introductory video on the basics of using threads in C.
- [Philosophers Project Guide (Notion)](https://suspectedoceano.notion.site/Philosophers-b1bf3c57eee6420cafa7d0900b3d3216) - A detailed breakdown and guide for the Philosophers project.
- [POSIX Threads Programming](https://hpc-tutorials.llnl.gov/posix/) - A comprehensive tutorial on pthreads, which is the core of this project.
### Documentation
- `pthread_create()` - Create a new thread
- `pthread_join()` - Wait for thread termination
- `pthread_mutex_init()` - Initialize a mutex
- `pthread_mutex_lock()` - Lock a mutex
- `pthread_mutex_unlock()` - Unlock a mutex
- `pthread_mutex_destroy()` - Destroy a mutex
- `gettimeofday()` - Get current time
- `usleep()` - Suspend execution for microsecond intervals

### AI Usage
AI assistance (Claude) was used for:
- Code review 
- Analysis of race conditions and synchronization issues and explain them well
- Debugging guidance for threading issues and help with the tools

AI was **not** used for:
- Core algorithm implementation
- Mutex and threading logic design
- Initial project architecture

## Implementation Details

### Project Structure
```
philosophers/
├── inc/
│   ├── philo.h          # Main header with structures and function prototypes
│   └── colors.h         # ANSI color codes for terminal output
└── src/
    ├── philo.c          # Main program and simulation start
    ├── check_input.c    # Input validation and parsing
    ├── init_philos.c    # Initialization of philosophers and forks
    ├── destroy_philos.c # Cleanup and memory deallocation
    ├── philo_helper.c   # Helper functions (eating, thinking, fork management)
    ├── state_check.c    # Death detection and simulation state management
    ├── time.c           # Time utilities
    └── error.c          # Error handling
```

### Key Features
- **Even/Odd Fork Strategy**: Even-numbered philosophers pick up forks in a different order than odd-numbered ones to prevent deadlock
- **Monitoring Thread**: A separate thread monitors all philosophers for death conditions
- **Precise Timing**: Custom sleep function to achieve accurate timing within millisecond precision
- **Thread-Safe Operations**: All shared data is protected by mutexes
- **Color-Coded Output**: Different actions are displayed in different colors for easier visualization

### Algorithm
1. Initialize all philosophers and forks
2. Start simulation with synchronized timestamp
3. Each philosopher thread alternates between:
   - Taking forks (in order based on even/odd ID)
   - Eating (updating last meal time)
   - Releasing forks (in reverse order)
   - Sleeping
   - Thinking
4. Monitor thread continuously checks for:
   - Philosopher death (time since last meal > time_to_die)
   - Completion condition (all philosophers ate required meals)
5. Simulation stops when death occurs or all philosophers are full

### Edge Cases Handled
- Single philosopher (will always die after time_to_die)
- Very short time values
- Maximum number of philosophers (200)
- Input validation for all parameters

## Author

**moodeh** - 42 Student

---

*For any issues or questions about this implementation, please refer to the 42 subject or consult the resources listed above.*
