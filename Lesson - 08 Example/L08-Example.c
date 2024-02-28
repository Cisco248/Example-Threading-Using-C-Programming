#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = { 2, 3, 5, 7, 9, 11, 13, 15, 17, 19 };

void* routine(void* arg) {
    int index = *(int*)arg;
    int sum = 0;
    for (int j = 0; j < 2; j++) {
        sum += primes[index + j];
    }
    printf("Local Sum: %d\n", sum);
    *(int*)arg = sum;
    return arg;
}

int main (int argc, char* argv[]) {
    pthread_t th[2];
    int i;
    for (i = 0; i < 2; i++) {
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0) {
            perror("Failed to Create Thread !!!");
        }
    }
    int globalSum = 0;
    for (i = 0; i < 2; i++) {
        int* r;
        if (pthread_join(th[i], &r) != 0) {
            perror("Failed to Join Thread !!!");
        }
        globalSum += *r;
        free(r); 
    }
    printf("Global Sum: %d\n", globalSum);
    return 0;
}