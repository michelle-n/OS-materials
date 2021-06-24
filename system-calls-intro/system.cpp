/*
* Example of system to run ls -a command.
* https://man7.org/linux/man-pages/man3/system.3.html 
*/

#include <stdlib.h>

int main() {
  
    // Use system to run ls -a command
    system("ls -a");

    return 0;
}
