/*lecture exercise but single thread, use 'time' and compare it with the lecture exercise / two threaded version!! */


#include <stdio.h>
#include <stdlib.h>


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

    
    int64_t result = 0;
    for (int64_t i = 0; i<=num; i++){
        result = result+i;
    }

    // sum up the global variables (for the odd and even sum)
    printf ("Take the sum of numbers from 1 to %ld results in: %ld\n", num, result);

}
