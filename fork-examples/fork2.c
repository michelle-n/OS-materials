/* Fork example from lecture 
  CPSC 457 Fall 2020, Lecture Slides: 06 – processes, slide 18 (Dr. Pavol Federl)
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main() 
{
    for(int i=0 ; i<4 ; i++ ) {
        fork();
    }
    printf("X\n");
}


