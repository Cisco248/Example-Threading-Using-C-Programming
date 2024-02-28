#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

void* roll_dice() {
    int value = (rand() % 6) + 1;
    int* result = malloc(sizeof(int));
    *result = value;
    sleep(2);
    printf("Thread Result: %p\n", result);
    pthread_exit((void*) result);
}

int main(int argc, char* argv[]) {
    int* res;
    srand(time(NULL));
    pthread_t t1, t2, t3, t4;
    if (pthread_create(&t1, NULL, &roll_dice, NULL) != 0) {
        return 1;
    }
    if (pthread_join(t1, (void**) &res) != 0) {
        return 2;
    }
    printf("Main Result: %p\n", res);
    printf("Result: %d\n", *res);
    free(res);
    pthread_exit(0);
}