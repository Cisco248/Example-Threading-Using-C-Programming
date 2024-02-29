## Introduction
A mutex (short for mutual exclusion) is a synchronization mechanism that is used to ensure that only one thread can access a shared resource or critical section at a time. This prevents data corruption and race conditions, where multiple threads try to access and modify shared data simultaneously. Mutexes provide a way to coordinate access to shared resources in a multithreaded program.

Let's look at a simple example in C using pthreads:

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

int sharedVariable = 0;
pthread_mutex_t mutex;

void* incrementFunction(void* threadID) {
    long tid = (long)threadID;

    for (int i = 0; i < 5; i++) {
        // Lock the mutex before accessing the shared resource
        pthread_mutex_lock(&mutex);

        // Critical section: Access and modify the shared resource
        sharedVariable++;
        printf("Thread %ld incremented sharedVariable to %d\n", tid, sharedVariable);

        // Unlock the mutex after finishing the critical section
        pthread_mutex_unlock(&mutex);

        // Simulate some other work or delay
        usleep(100000);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    for (long t = 0; t < NUM_THREADS; t++) {
        rc = pthread_create(&threads[t], NULL, incrementFunction, (void*)t);
        if (rc) {
            printf("Error: Unable to create thread %ld\n", t);
            exit(-1);
        }
    }

    // Wait for threads to finish
    for (long t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    // Print the final value of the shared variable
    printf("Final sharedVariable value: %d\n", sharedVariable);

    return 0;
}
```

In this example, we have a shared variable `sharedVariable` that multiple threads increment within a critical section. The `pthread_mutex_t mutex` is used to protect access to this critical section. The `pthread_mutex_lock` function is called before entering the critical section, and `pthread_mutex_unlock` is called after leaving it.

This ensures that only one thread can be inside the critical section at a time, preventing race conditions and ensuring that the shared resource is updated correctly. The `usleep` function is used to simulate some work being done inside the critical section.
