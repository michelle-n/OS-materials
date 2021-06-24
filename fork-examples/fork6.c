/* Fork Example modified from Emmanuel Onu's Code (CPSC 457 Spring 2020) */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

  pid_t id ;
  id = fork() ;

  // Print out process id values returned from fork call
  printf("id value : %d\n",id);

  // Check if error occurred
  if (id < 0) {
    fprintf(stderr, "Fork Failed");
    exit(-1);
  }
  else if ( id == 0 ) // else if (child)
  {
    printf ( "Child : Hello I am the child process\n");
    printf ( "Child : Child’s PID: %d\n", getpid());
    printf ( "Child : Parent’s PID: %d\n", getppid());
    execlp("/bin/ls", "ls", NULL); // execlp replaces child process image with that of ls
    printf("I shouldn't be printing..."); // therefore, this line should not print unless execlp failed
  }
  else // else if (parent)
  {
    printf ( "Parent : Hello I am the parent process\n" ) ;
    printf ( "Parent : Parent’s PID: %d\n", getpid());
    printf ( "Parent : Child’s PID: %d\n", id);
    wait(NULL); // waits for child to terminate
    printf (" Bye from parent! \n");
    exit(0);
  } 

}

