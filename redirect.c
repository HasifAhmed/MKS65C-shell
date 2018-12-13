#include <string.h> //strcmp()
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include "redirect.h"
#include "shell.h"
#include <ctype.h>
#include <errno.h>










/* void check(char* command)
Inputs:  char* command
Returns: 0
reds based on > or <. Currenty space issues!!!
*/
int check(char * command){
  char **redir = calloc( 10 , sizeof(char*));
  char com[1024];
  strcpy(com,command);
  int arg = 0;
      while(command){
        if( strchr(com, '>')){
          redir[arg] = strsep(&command, ">" );

          //printf("%s", redir[arg]);

        } else {
          redir[arg] = strsep(&command, "<" );

        }
        arg++;
      }

      //redir[arg] = command;
      //printf("\n%s\n", redir[0]);
      //printf("\n%s\n", redir[1]);

        if(strchr(com, '>')){
          int tmp = dup(STDOUT_FILENO);

          int file = open(redir[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);

          if(file < 0){
            printf("File Not Found\n");
            return 0;
          }
          dup2(file, STDOUT_FILENO);


          run_each(redir[0]);

          dup2(tmp, STDOUT_FILENO);
          close(file);
          free(redir);
          return 0;
        }
        if(strchr(com, '<')){
          int tmp2 = dup(STDIN_FILENO);

          int file2 = open(redir[1], O_RDONLY, 0644);
          if(file2 < 0){
            printf("File Not Found\n");
            return 0;
          }
          dup2(file2, STDIN_FILENO);


          run_each(redir[0]);

          dup2(tmp2, STDIN_FILENO);
          close(file2);
          free(redir);
          return 0;
        }
        free(redir);
        return 0;
  /*
  char ** parsed_args = calloc (10, sizeof(char*));
  parsed_args = parse_args(command);
  int fd = 0;
  if(!fork()){
    int index = 0;
    int red = -1;
    while(parsed_args[index]){
      printf("parsedargs[%d]: %s\n", index,parsed_args[index]);
      if(strcmp(parsed_args[index],">") == 0){
        printf("parsedargs[%d]: %s\n", index, parsed_args[index]);
        fd = open(parsed_args[2], O_WRONLY | O_CREAT,  0644);
        if(fd == -1){
          printf("%s\n",strerror(errno));
          return 1;
        }
        dup2(fd,STDOUT_FILENO);
        red = index;
      }
      /*
      if(strcmp(parsed_args[index],"<") == 0){
        printf("parsedargs[index]: %s\n", parsed_args[index]);
        int fd = open(parsed_args[index + 1], O_RDONLY);
        dup2(fd, 0);
        red = index;
      }
      index++;
    }
    //dup2(fd,STDOUT_FILENO);
    while(parsed_args[index]){
      printf("parsedargs[index]: %s\n", parsed_args[index]);
    }
    int err = execvp(parsed_args[0],parsed_args);
    if ( err == -1){
       printf("Fail: %s\n", strerror(errno));
       exit(0);
      }
    return 1;
  } else {
    int p, status;
    p = wait(&status);

    free(parsed_args);
    //free(pop);
    return 1;
  }
  */
}
