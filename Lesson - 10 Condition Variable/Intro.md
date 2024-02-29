## Introduction
A condition variable is a synchronization primitive used in multithreaded programming to allow threads to wait for a specific condition to become true before proceeding. Condition variables are typically used in conjunction with mutexes to manage access to shared resources.

Here's an example to illustrate the concept of condition variables in C using pthreads:

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_BUFFER_SIZE 5

int buffer[MAX_BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_producer = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_consumer = PTHREAD_COND_INITIALIZER;

void* producer(void* arg) {
    for (int i = 0; i < 10; ++i) {
        pthread_mutex_lock(&mutex);

        // Check if the buffer is full
        while (count == MAX_BUFFER_SIZE) {
            // If the buffer is full, wait for the consumer to signal that space is available
            pthread_cond_wait(&cond_producer, &mutex);
        }

        // Produce an item and add it to the buffer
        buffer[count++] = i;
        printf("Produced: %d\n", i);

        // Signal the consumer that a new item is available
        pthread_cond_signal(&cond_consumer);

        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; ++i) {
        pthread_mutex_lock(&mutex);

        // Check if the buffer is empty
        while (count == 0) {
            // If the buffer is empty, wait for the producer to signal that an item is available
            pthread_cond_wait(&cond_consumer, &mutex);
        }

        // Consume an item from the buffer
        int item = buffer[--count];
        printf("Consumed: %d\n", item);

        // Signal the producer that there is space in the buffer
        pthread_cond_signal(&cond_producer);

        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Create threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Clean up resources
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_producer);
    pthread_cond_destroy(&cond_consumer);

    return 0;
}
```

In this example, a producer thread produces items and adds them to a shared buffer, while a consumer thread consumes items from the buffer. The condition variables `cond_producer` and `cond_consumer` are used to signal and wait for specific conditions.

Here's how it works:

- The `pthread_cond_wait` function is used to make a thread wait until a condition is signaled. It is always used inside a while loop that checks the actual condition because spurious wake-ups (unexpected wake-ups without a real signal) can occur.

- When the producer adds an item to the buffer, it signals the consumer using `pthread_cond_signal(&cond_consumer)`, indicating that there is an item available for consumption.

- The consumer, upon consuming an item, signals the producer using `pthread_cond_signal(&cond_producer)`, indicating that there is space available in the buffer for a new item.

- The use of condition variables helps avoid busy-waiting and allows threads to sleep efficiently until the required condition is met, improving overall performance and resource utilization.

In summary, condition variables provide a way for threads to communicate about the state of shared data and coordinate their activities, enabling more efficient and synchronized multithreaded programming.
