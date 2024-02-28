#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

int fuel = 0;
pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;

void* fuel_filling(void* arg) {
    for(int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutexFuel);
        fuel += 30;
        printf("Filled Fuel ... : %d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_broadcast(&condFuel);
        sleep(1);
    }
}

void* car(void* arg) {
    pthread_mutex_lock(&mutexFuel);
    while (fuel < 40) {
        printf("No Fuel !!!\n");
        pthread_cond_wait(&condFuel, &mutexFuel);
    }
    fuel -= 40;
    printf("Got Fuel.\n");
    pthread_mutex_unlock(&mutexFuel);
}

int main (int argc, char* argv[]) {
    pthread_t th[6];
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);
    for (int i = 0; i < 6; i++) {
        if ( i == 4 || i == 5 ) {
            if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0) {
                perror("Failed to Create Thread !!");
            }
        }
        else {
            if (pthread_create(&th[i], NULL, &car, NULL) != 0) {
                perror("Failed to Create Thread !!"); 
            }
        }
        
    }
    for (int i = 0; i < 6; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to Joint Thread !!");
        }
    }
    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return 0;
}