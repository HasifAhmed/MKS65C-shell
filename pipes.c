#include <string.h> //strcmp()
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include "shell.h"
#include "pipes.h"
#include <ctype.h>
#include <errno.h>




/* void piping(char* input)
Inputs:  char* input
Returns: 0
Runs pipe commands
*/

int piping(char *input){
  char * pipi = strchr(input,'|');
  char* x = input;
  pipi[0] = 0;
  char * y = pipi + 1;
  char **parse1 = calloc(1024, sizeof(char*));
  char ** parse2 = calloc(1024,sizeof(char*));
  parse1 = parse_args(x);
  parse2 = parse_args(y);
  int pipes[2];
  pipe(pipes);
  if(!fork()){
    dup2(pipes[1], 1);
    close(pipes[0]);
    execvp(parse1[0], parse1);

    int p, status;
    p = wait(&status);
    
  }
  else {
      //wait(NULL);
    dup2(pipes[0], 0);
    close(pipes[1]);
    execvp(parse2[0],parse2);

    int p, status;
    p = wait(&status);

  }

  free(parse1);
  free(parse2);

  return 0;


}
