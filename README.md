# Introduction to UNIX Threads in C

This repository provides a simple introduction to using UNIX threads in the C programming language. Threads offer a way to achieve concurrent execution within a process, enabling parallelism and improved program performance.

## Table of Contents ✨

- [Getting Started](#getting-started)
- [Understanding Threads](#understanding-threads)
- [Lessons With Examples](#Lessons-With-Examples)
- [Example Code](#example-code)
- [Building and Running](#building-and-running)
- [Contributing](#contributing)
- [License](#license)

## Getting Started ✨

To get started with UNIX threads in C, make sure you have a UNIX-like operating system, such as Linux or macOS, where POSIX threads (`pthread`) are supported.

## Understanding Threads ✨

In a nutshell, a thread is the smallest unit of execution within a process. Unlike separate processes, threads within the same process share the same code and data but have their own execution stack. This allows for efficient communication and data sharing between threads.

Threads are typically created using the `pthread_create` function, and they share resources such as file descriptors, heap memory, and global variables. Proper synchronization mechanisms, like mutexes and condition variables, are used to manage shared resources and avoid race conditions.

## Lessons With Examples ✨

- Lesson 01 - What is Thread and Sample Code
- Lesson 02 - Difference Between Threads vs Processes
- Lesson 03 - Race Condition Using Mutexlock
- Lesson 04 - What is Mutexlock?
- Lesson 05 - Threads in Loops
- Lesson 06 - Threads Join
- Lesson 07 - Pass Argument
- Lesson 08 - Excersice Code for Study
- Lesson 09 - Difference Between Trylock and Lock
- Lesson 10 - Codition Variable [ wait, broadcast, signal ]
- Lesson 11 - Example for Trylock
- Lesson 12 - Define the pthread_exit()
- Lesson 13 - Explain the pthread_barrier [ wait, init, destroy ]
- Lesson 14 - Example for the Barrier

## Example Code ✨

Check the provided [example code](example.c) in this repository for a simple demonstration of creating and managing threads in C. The example creates multiple threads, each running a function, and showcases basic thread synchronization.

```c
#include <stdio.h>
#include <pthread.h>

// Function to be executed by each thread
void* threadFunction(void* arg) {
    // Thread-specific code
    // ...

    pthread_exit(NULL);
}

int main() {
    // Code to create and manage threads
    // ...

    return 0;
}
```

## Building and Running ✨

To build the example code, use a C compiler that supports POSIX threads. For instance, with GCC, compile the code using the following command:

```bash
gcc example.c -o example -pthread
```

Run the compiled executable:

```bash
./example
```

## Contributing ✨

Contributions are welcome! If you have improvements or additional examples, feel free to submit a pull request.

## License ✨

This project is licensed under the [MIT License](LICENSE).
```

Feel free to customize this template based on your specific project details and requirements.
