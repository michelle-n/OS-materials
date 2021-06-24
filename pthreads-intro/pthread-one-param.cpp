/*lecture exercise, passing single param example*/


#define NDEBUG // Notice that this statement occurs BEFORE assert.h is included

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <iostream>

#include <cassert>


int64_t oddSum;
int64_t evenSum;


void * sumOdd(void * a){

    int64_t num = (int64_t) a;

    // create a local counter
    int64_t counter = 0;

    // sum all the odd numbers
    for(int64_t i = 1; i <= num; i = i+2){
        counter = counter + i;
    }

    std::cout << "Counter: " << counter << std::endl;

    // update global var oddSum
    oddSum = counter;

    std::cout << "Odd sum: " << oddSum << std::endl;

    // once it's finished, we want to use pthread_exit
    pthread_exit(NULL);

}


/* Sums the even numbers from 0 to n
    @param n - the number to sum to
 */
void * sumEven(void * n){

    int64_t num = (int64_t) n;

    assert(num > 0); 

    // create a local counter
    int64_t counter = 0;

    // sum all the even numbers
    for(int64_t i = 0; i <= num; i = i+2){
        counter = counter + i;
    }

    // update global var evenSum
    evenSum = counter;

    assert(evenSum % 2 == 0);

    // once it's finished, we want to use pthread_exit
    pthread_exit(NULL);

}

int main(int argc, char* argv[]){

    int64_t num;

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
    pthread_create(&threads[0], NULL, sumOdd, (void *)num);
    pthread_create(&threads[1], NULL, sumEven, (void *)num);

    // wait for the threads to finish
    for (int i = 0; i < numberOfThreads; i++){
        pthread_join(threads[i], NULL);
    }

    // sum up the global variables (for the odd and even sum)
    int64_t result = oddSum + evenSum;
    printf ("Take the sum of numbers from 1 to %ld results in: %ld\n", num, result);

}
