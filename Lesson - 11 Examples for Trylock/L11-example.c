// Cheif = Threads
// Stoves = Shared Data(+mutex)

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

pthread_mutex_t stoveMutex[4];
int stoveGas[4] = { 100, 100, 100, 100 };

void* routine (void* args) {
    for (int i = 0; i < 4; i++) {
        if (pthread_mutex_trylock(&stoveMutex[i]) == 0) {
            int fuelNeeded = (rand() % 30);
            if (stoveGas[i] - fuelNeeded < 0) {
                printf("No More Gas... Go to the Shop\n");
            }
            else {
                stoveGas[i] -= fuelNeeded;
                printf("Gas Left %d\n", stoveGas[i]);
            }
            pthread_mutex_unlock(&stoveMutex[i]);
            break;
        }
        else {
            if (i == 3) {
                printf("Stove Not Available... All Are Busy....\n");
                usleep(300000);
                i = 0;
            }
        }
    }
}

int main (int argc, char* argv[]) {
    srand(time(NULL));
    pthread_t th[10];
    for ( int i = 0; i < 4; i++) {
        pthread_mutex_init(&stoveMutex[i], NULL);
    }
    for (int i = 0; i < 10; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
            perror("Failed to Create Thread !!!");
        }
    }
    for(int i = 0; i < 10; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to Join Thread !!!");
        }
    }
    for ( int i = 0; i < 4; i++) {
        pthread_mutex_destroy(&stoveMutex[i]);
    }
    return 0;
}