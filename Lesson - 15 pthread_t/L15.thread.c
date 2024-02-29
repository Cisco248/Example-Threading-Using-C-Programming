#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define THREAD_NUM 2

void* routine(void* args) {
    pthread_t th = pthread_self();
    printf("%ul\n", th);
}

int main (int argc, char* argv[]) {
    pthread_t th[THREAD_NUM];
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
            perror("failed to create thread !!!");
        }
        printf("%ul\n", th[i]);
    }   

    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("failed to join thread !!!");
        }
    }

    return 0;
}