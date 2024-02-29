
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <semaphore.h>

#define THREAD_NUM 16

sem_t semaphore;

void* routine(void* args) {
    printf("(User : %d) - Waiting in the Login Queue\n", *(int*)args);
    printf("-------------------------------------------------\n");
    sem_wait(&semaphore);
    printf("(User : %d) - Logged in Successfully !!!\n", *(int*)args);
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    sleep(rand() % 5 + 1);
    printf("(User : %d) - Logged Out Successfully !!!\n", *(int*)args);
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    sem_post(&semaphore);
    free(args);
}

int main (int argc, char *argv[]) {
    pthread_t th[THREAD_NUM];
    sem_init(&semaphore, 0, 2);
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0) {
            perror("Failed to Create Thread !!!");
        } 
    }

    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to Join Thread !!!");  
        }
    }
    sem_destroy(&semaphore);
    return 0;
}