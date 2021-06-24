/*
* Example of execvp to run ls -a command.
* https://man7.org/linux/man-pages/man3/exec.3.html
*/
#include <stdlib.h>
#include <iostream>
#include <unistd.h>


int main() {
  
    // Use execvp to run ls -a command
    execlp("/bin/ls","ls","-a",(char *) 0);

    // "The exec() family of functions replaces the current process image with a new process image."
    // i.e. if successful, the below lines will not be run
    std::cout << "I shouldn't be printing" << std::endl;

    return 0;

}
