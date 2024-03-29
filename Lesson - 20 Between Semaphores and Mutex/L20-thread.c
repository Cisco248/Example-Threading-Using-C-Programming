/*
This Example Using the Semaphores
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <semaphore.h>

#define THREAD_NUM 4

sem_t semFuel;
pthread_mutex_t mutexFuel;

int fuel = 50;

void* routine1(void* args) {
    while (1) {
        sem_wait(&semFuel);
        fuel += 50;
        printf("Current Volume : %d\n", fuel);
    }
}

void* routine2(void* args) {
    while (1) {
        sem_post(&semFuel);
        usleep(100000);
    }
}

int main (int argc, char *argv[]) {
    pthread_t th[THREAD_NUM];
    sem_init(&semFuel, 0, 1);
    pthread_mutex_init(&mutexFuel, NULL);
    int i;

    for (i = 0; i < THREAD_NUM; i++) {
        if (i % 2 == 0) {
           if (pthread_create(&th[i], NULL, &routine1, NULL) != 0) {
                perror("Failed to Create Thread !!!");
            }  
        } else {
            if (pthread_create(&th[i], NULL, &routine2, NULL) != 0) {
                perror("Failed to Create Thread !!!");
            }
        }
    }

    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to Join Thread !!!");  
        }
    }
    sem_destroy(&semFuel);
    pthread_mutex_destroy(&mutexFuel);
    return 0;
}