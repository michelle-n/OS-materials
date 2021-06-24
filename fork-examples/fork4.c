/* Modified fork example from lecture 
  CPSC 457 Fall 2020, Lecture Slides: 06 – processes, slide 16 (Dr. Pavol Federl)
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int x = 10;
int main()
{
    printf("x=%d\n", x);
    pid_t id = fork();
    if (id == 0) x ++;
    printf("x=%d\n", x);
}

