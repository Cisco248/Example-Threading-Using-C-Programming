/* 
    Threads Without the Race Condition
    **********************************

    void* routine() {
        for (int i = 0; i < 1000000; i++)
        {
            mails++;
        }

    Output: Number of Mails: 2000000
    
    # This is the Maximum Time run with out Race Condition

    void* routine() {
        for (int i = 0; i < 10000000; i++)
        {
            mails++;
        }

    Output: Number of Mails: 13400000

    # This Output is Not Correct! 
        Because, It's Large Number. Firstly Thread 1 Finished to Start the Thread 2 Task. 

                t1 Read = 1000000,
                t1 Increament = 1000000, 
                t1 Write = 1030500

                t2 Read = 1030500,
                t2 Increament = 1030500,
                t2 Write = 10305555

        That's the Reason. !

    Let's Use the Race Condition 
    ****************************
    
    


}*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int mails = 0;

void* routine() {
    for (int i = 0; i < 10000000; i++)
    {
        mails++;
    }
}

int main(int argc, char* argv[]) {
    pthread_t p1, p2;

    pthread_create(&p1, NULL, &routine, NULL);
    pthread_create(&p2, NULL, &routine, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("Number of Mails: %d\n", mails);
    return 0;
}

