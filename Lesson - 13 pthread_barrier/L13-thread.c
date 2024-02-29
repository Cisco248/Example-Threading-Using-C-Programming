#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

/* 
pthread_barrier_ t 
------------------

this barrier provide the blocking the threads for while momment. 
we have 2 threads and after run it it's not working. 
because these threads blocking after didn't unblocking process.
after we use the more than 2 threads now this function working. 
*/


pthread_barrier_t barrier;

void* routine(void* args) {
    while (1){
        printf(">! >! >! Waiting at the Barrier >! >! >!\n");
        sleep(1);
        pthread_barrier_wait(&barrier);
        printf("> > > Passed the Barrier > > >\n");
        break;
    }
}

int main(int argc, char* argv[]) {
    pthread_t th[10];
    int i;
    pthread_barrier_init(&barrier, NULL, 10);
    for (int i = 0; i < 10; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
            perror("Failed to Create Thread !!!");
        }
    }
    for (int i = 0; i < 2; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to Join Thread !!!");
        }
    }
    pthread_barrier_destroy(&barrier);
    return 0;
}