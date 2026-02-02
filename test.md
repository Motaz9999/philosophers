Of course. I've updated the `Resources` section of your `README.md` to include the new links and clarify the use of AI as a learning model.

Here is the complete, updated file. You can replace the content of your `README.md` with this.

---

```markdown
_This project has been created as part of the 42 curriculum by <moodeh>._

# Philosophers

## Description

This project is a classic synchronization problem and a staple of concurrent algorithm design. The goal is to solve the "Dining Philosophers" problem, where a number of philosophers sit around a table and alternate between thinking and eating.

There is one fork between each philosopher. To eat, a philosopher must pick up both the fork to their left and the fork to their right. The challenge is to implement a solution where no philosopher starves and the simulation avoids common concurrency issues like **deadlocks** and **race conditions**.

This implementation uses POSIX threads (`pthreads`) to represent the philosophers and mutexes (`pthread_mutex_t`) to represent the forks. A dedicated monitor thread oversees the simulation, checking for philosopher deaths or the completion of meals.

## Instructions

### Compilation

To compile the project, navigate to the project directory and run `make`:

```bash
make
```

### Execution

The program is run from the command line with the following arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_to_eat]
```

**Arguments:**
*   `number_of_philosophers`: The number of philosophers (and forks) at the table.
*   `time_to_die` (ms): If a philosopher has not started eating in this amount of time since their last meal or the start of the simulation, they die.
*   `time_to_eat` (ms): The time it takes for a philosopher to eat.
*   `time_to_sleep` (ms): The time it takes for a philosopher to sleep.
*   `[meals_to_eat]` (optional): If specified, the simulation stops once every philosopher has eaten this many times.

**Example:**

```bash
./philo 5 800 200 200 7
```
This will start a simulation with 5 philosophers who must eat 7 times. They have 800ms to eat before they die, and each eating/sleeping cycle takes 200ms.

## Resources

### Documentation & Articles
*   call creates parent and child processes.
*  
*   
*   
*   [**GeeksforGeeks: Dining Philosophers Problem**](https://www.geeksforgeeks.org/dining-philosopher-problem-using-semaphores/) - A good overview of the problem and common solutions.
*  resource for understanding the precise behavior of mutex functions.

### AI Usage

**Google's Gemini** was used as an interactive learning model and assistant for several key tasks throughout the project:

*   **Testing & Tooling:**
    *   Generated a custom Python (`tester.py`) script to perform logic checks on the program's output, verifying death timings and meal limits.
    *   Created a shell script (`stress.sh`) to run the program hundreds of times in quick succession to detect rare data races or deadlocks.
    *   Wrote an animated `Makefile` to provide a cleaner and more visual compilation experience.

*   **Debugging:**
    *   Helped analyze the output of `valgrind --tool=helgrind` to identify the initial data race on the `end_simulation` flag.
    *   Diagnosed a critical logic bug where an inverted `if` condition was causing philosophers to die when they should have been alive.
    *   Explained and provided solutions for the `FATAL: ThreadSanitizer: unexpected memory mapping` error, identifying it as a toolchain/environment issue rather than a code bug.

*   **Documentation:**
    *   Generated and updated this `README.md` file based on the project's requirements, code, and our development history.
```