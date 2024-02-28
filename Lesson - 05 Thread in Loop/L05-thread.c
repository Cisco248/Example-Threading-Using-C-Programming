#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int mail = 0;
pthread_mutex_t mutex;

void* routine() {
    for (int i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&mutex);
        mail++;
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char* argv[]) {
    pthread_t p[4];
    int i;
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < 4; i++) {
        if (pthread_create(p + i, NULL, &routine, NULL) != 0) {
            perror("Failed to Create Thread");
            return 1;
        }
        printf("Thread %d has Started\n", i);
        if (pthread_join(p[i], NULL) != 0) {
            return 2;
        }
        printf("Thread %d has Ended\n", i);
    }
    pthread_mutex_destroy(&mutex);
    printf("Number of Mails: %d\n", mail);
    return 0;
}