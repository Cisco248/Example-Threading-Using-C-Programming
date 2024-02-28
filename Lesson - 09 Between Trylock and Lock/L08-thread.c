#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

void* routine() {
    pthread_mutex_lock(&mutex);
    printf("Got Lock\n");
    sleep(1);
    pthread_mutex_unlock(&mutex);
}

int main (int argc, char* argv[]) {
    pthread_t th[4];
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < 4; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
            perror("Error at Creating Thread !!!");
        }
    }
    for (int i = 0; i < 4; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Error at Joining Thread !!!");
        }
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}