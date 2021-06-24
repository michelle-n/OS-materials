/*lecture exercise: see 08-threads (slide 27) */


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


int64_t num;
int64_t oddSum;
int64_t evenSum;


void * sumOdd(void * a){

    // sums all the odd numbers
    int64_t counter = 0;
    for(int64_t i = 1; i <= num; i = i+2){
        counter = counter + i;
    }
    oddSum = counter;

    // once it's finished, we want to use pthread_exit
    pthread_exit(NULL);

}

void * sumEven(void * a){

    // sums all the even numbers
    int64_t counter = 0;
    for(int64_t i = 0; i <= num; i = i+2){
        counter = counter + i;
    }
    evenSum = counter;

    // once it's finished, we want to use pthread_exit
    pthread_exit(NULL);

}

int main(int argc, char* argv[]){

    // take in the command line arg
    if (argc != 2){
        printf("Usage: %s N\n", argv[0]);
        printf("\t N - the integer number, where this program calculates the sum from 1..N\n");
        return 1;
    } else{
        num = atol(argv[1]);
    }

    // set oddSum and evenSum to 0
    oddSum = 0;
    evenSum = 0;
    
    int numberOfThreads = 2;
    // declare the threads
    pthread_t threads[numberOfThreads];

    // create the threads
    pthread_create(&threads[0], NULL, sumOdd, NULL);
    pthread_create(&threads[1], NULL, sumEven, NULL );

    // wait for the threads to finish
    for (int i = 0; i < numberOfThreads; i++){
        pthread_join(threads[i], NULL);
    }


    // sum up the global variables (for the odd and even sum)
    int64_t result = oddSum + evenSum;
    printf ("Take the sum of numbers from 1 to %ld results in: %ld\n", num, result);

}
