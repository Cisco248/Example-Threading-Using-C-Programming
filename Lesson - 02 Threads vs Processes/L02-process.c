#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int x = 2;
    int pid = fork();
    if (pid == -1) {
        return 1;
    }

    if (pid == 0) {
        x++;
    }

    sleep(2);

    printf("Value of X: %d\n", x);
    if (pid != 0) {
        wait(NULL);
    }

    printf("Process of ID: %d\n", getpid());
    if (pid != 0) {
        wait(NULL);
    }

    return 0;
}