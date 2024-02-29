/*

This Example Show the Mutex lock
--------------------------------

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

#define THREAD_NUM 8

pthread_mutex_t mutexFuel;
int fuel = 50; 

void* routine(void* args) {
    pthread_mutex_lock(&mutexFuel);
    fuel += 50;
    printf("Incremented Fuel to : %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
}

int main (int argc, char* argv[]) {
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexFuel, NULL);
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
            perror("Failed to Create Thread !!!");
        }
        
    }
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to Join Thread !!!");  
        }
        
    }
    pthread_mutex_destroy(&mutexFuel);
    return 0;
}