/* Fork example from lecture 
  CPSC 457 Fall 2020, Lecture Slides: 06 – processes, slide 21 (Dr. Pavol Federl)
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int x = 10;
int main()
{
    printf("x=%d\n", x);
    fork();
    x ++;
    printf("x=%d\n", x);
}

