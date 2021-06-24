/*lecture exercise, passing multiple params*/


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string>


int64_t oddSum;
int64_t evenSum;


struct Multiparam{
    int64_t num;
    std::string phrase;
};

void * sumOdd(void * a){

    struct Multiparam * myParams = ((struct Multiparam *)a);

    int64_t num = myParams->num;
    std::string phrase = myParams->phrase;

    // sums all the odd numbers
    for(int64_t i = 1; i <= num; i = i+2){
        oddSum = oddSum + i;
    }

      printf("%s %ld\n", phrase.c_str(), oddSum);

    // once it's finished, we want to use pthread_exit
    pthread_exit(NULL);

}

void * sumEven(void * a){

    struct Multiparam * myParams = ((struct Multiparam *)a);

    int64_t num = myParams->num;
    std::string phrase = myParams->phrase;

    // sums all the even numbers
    for(int64_t i = 0; i <= num; i = i+2){
        evenSum = evenSum + i;
    }

    printf("%s %ld\n", phrase.c_str(), evenSum);

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

    // make the thread params structs
    Multiparam threadparams[numberOfThreads];
    for (int i=0; i < numberOfThreads; i++){
        threadparams[i].num = num;
        threadparams[i].phrase = "the sum for thread " + std::to_string(i) + " is: ";
    }

    // create the threads
    pthread_create(&threads[0], NULL, sumOdd, &threadparams[0]);
    pthread_create(&threads[1], NULL, sumEven, &threadparams[1]);

    // wait for the threads to finish
    for (int i = 0; i < numberOfThreads; i++){
        pthread_join(threads[i], NULL);
    }


    // sum up the global variables (for the odd and even sum)
    int64_t result = oddSum + evenSum;
    printf ("Take the sum of numbers from 1 to %ld results in: %ld\n", num, result);

}
