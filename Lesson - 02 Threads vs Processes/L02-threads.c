#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int x = 1;

void* routine() {
    x++;
    sleep(2);
    printf("Value of X: %d\n", x);
}

void* routine2() {
    sleep(2);
    printf("Value of X: %d\n", x);
}

int main(int argc, char* argv[]) {
    pthread_t t1, t2;

    if (pthread_create(&t1, NULL, &routine, NULL)) {
        return 1;
    }

    if (pthread_create(&t2, NULL, &routine2, NULL)) {
        return 2;
    }

    if (pthread_join(t1, NULL)) {
        return 3;
    }

    if (pthread_join(t2, NULL)) {
        return 4;
    }

    return 0;
}