/* Fork example from lecture 
  CPSC 457 Fall 2020, Lecture Slides: 06 – processes, slide 16 (Dr. Pavol Federl)
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  fprintf( stderr, "A\n");
  fork();
  fprintf( stderr, "B\n");
  fork();
  fprintf( stderr, "C\n");
}

