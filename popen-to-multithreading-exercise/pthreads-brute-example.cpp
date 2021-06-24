/*
*
*
* The previous brute force program implemented with pthreads. 
*
*/

#include <stdio.h>
#include <string>
#include <cstring>
#include <pthread.h>


#define PATH_MAX 1024

struct Range {
	int start_num, end_num;
};


/*
* test_pin
* Description: Uses popen execute secret_pin with a given test pin
* Params: std::string pin - the pin to be tested
* Return value: Bool true if secret_pin cracked, else false
*/
static bool test_pin(std::string pin){

    FILE *fp;
    char path[PATH_MAX];

    // use popen to execute secret_pin with our param pin
    std::string cmd = "./secret_pin "+pin;
    fp = popen(cmd.c_str(), "r");

    // get the output from stream
    fgets(path, PATH_MAX, fp);

    // See if the string "Wrong" is not in the output of the tested './secret pin'
    if(strstr(path,"Wrong") == NULL){
        printf(path);
        pclose(fp);
        return true;
    } else {
        pclose(fp);
        return false;
    }
            
}


/*
* test_range
* Description: Starting routine for threads, tests pin on their given range
* Params: range struct:
*           -> start_num - start of of range to test pins
*           -> end_num - end of range to test pins
* Return value: void *
*/
void * test_range(void * a){

    struct Range * pin_range = ((struct Range *)a);
    int64_t start = pin_range->start_num;
    int64_t end = pin_range->end_num;

    bool found = false;

    // recall: each pin is a number from 0 to 9999 with some 0s prepended
    for(int num = start; num < end ; num++){

        // determine the number of leading zeros
        int leading_zeros = 0;
        if(num < 10) leading_zeros = 3;
        else if(num < 100) leading_zeros = 2;
        else if(num < 1000) leading_zeros = 1;

        // create a string for the pin and test it
        std::string pin = std::string( leading_zeros, '0')+std::to_string(num);
        found = test_pin(pin);
        if(found) break;
    }

    // once it's finished, use pthread_exit to terminate
    pthread_exit(NULL);

}

int main(void) {

    int numberOfThreads = 8;

    // declare the threads and their params
    pthread_t threads[numberOfThreads];
    Range ranges[numberOfThreads];

    // initialize range params, create the threads
    for(int i=0; i< numberOfThreads; i++){
        ranges[i].start_num = (10000) * i / numberOfThreads; // note the pins are from [0, 10000)
        ranges[i].end_num = (10000) * (i+1) / numberOfThreads;
        pthread_create(&threads[i], NULL, test_range, &ranges[i]);
    }

    // wait for the threads to finish
    for (int i = 0; i < numberOfThreads; i++){
        pthread_join(threads[i], NULL);
    }

    return 0;
}
