/*
* Example of popen to run ls -a command and read from stream.
* https://man7.org/linux/man-pages/man3/popen.3.html
* https://www.cplusplus.com/reference/cstdio/FILE/ 
*/

#include <stdio.h>

#define BUFF_MAX 255

int main() {

    // Use popen to run ls -a command
    FILE *filePtr;
    filePtr = popen("ls -a", "r");

    // Use fgets to read from stream
    char buff[BUFF_MAX];
    while (fgets(buff, BUFF_MAX, filePtr) != NULL){
        printf("%s", buff);
    }

    // Close stream
    pclose(filePtr);

    return 0;
}
