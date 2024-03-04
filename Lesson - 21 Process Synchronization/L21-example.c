#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
    int i = -10;
    int pid = fork();

    if (pid < 0) {
        printf("Fork Failed !");
        return -1;
    }

    if (pid == 0) {
        printf("i = %d\t address : %p\n", i, &i);
    }
    else {
        wait(NULL);
        printf("i = %d\t address : %p\n", i, &i);
    }
    return 0;
}