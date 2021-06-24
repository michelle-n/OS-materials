/*
*
* A brute force program to crack the secret_pin program. 
*
*
*/

#include <stdio.h>
#include <string>
#include <cstring>


#define PATH_MAX 1024

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


int main(void) {

    bool found = false;

    // recall: each pin is a number from 0 to 9999 with some 0s prepended
    for(int num = 0; num <= 9999 ; num++){

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

    return 0;
}
