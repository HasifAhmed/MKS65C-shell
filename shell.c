#include <string.h> //strcmp()
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include "shell.h"
#include <ctype.h>
char ** parse_args( char * line, char ** buff){

 int counter = 0;
 while(line){
   buff[counter] = strsep(&line, " ");
   counter++;
 }
 return buff;
}


int check(char * command){
      char **redir = malloc(1024 * sizeof(char *));
      char com[1024];
      strcpy(com,command);

      int arg = 0;
      while(command){
        if( strchr(com, '>')){
          redir[arg] = strsep(&command, ">");
          //printf("%s", redir[arg]);

        } else {
          redir[arg] = strsep(&command, "<");
        }
        arg++;
      }
      //redir[arg] = command;
      //printf("\n%s\n", redir[0]);
      //printf("\n%s\n", redir[1]);
      if(strchr(com, '>')){
        int tmp = dup(STDOUT_FILENO);

        int file = open(redir[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);

        dup2(file, STDOUT_FILENO);


        run_each(redir[0]);

        dup2(tmp, STDOUT_FILENO);
        close(file);
      }
      if(strchr(com, '<')){
        int tmp = dup(STDIN_FILENO);

        int file = open(redir[1],  O_WRONLY);

        dup2(file, STDIN_FILENO);

        run_each(redir[0]);
        dup2(tmp, STDIN_FILENO);
        close(file);

      }


    free(redir);

    return 0;
  }


int run_each(char * command){
  trim(command);
  if(strchr(command,'<') || strchr(command, '>')){
    int pid = fork();
    if(!pid){
      check(command);
    }
    int p, status;
    p = wait(&status);
    return 0;
  }

  if(strchr(command,'|')){
    int pid2 = fork();
    if(!pid2){
      piping(command);
    }
    int p, status;
    p = wait(&status);
    return 0;
  }

 char **parsed = malloc(1024 * sizeof(char *));
 parse_args(command, parsed);

 if(strcmp(parsed[0], "exit") == 0){
   //free(parsed);
   exit(0);
 }
 if(strcmp(parsed[0], "cd") == 0){
   if(chdir(parsed[1]) == -1){
     printf("BB-$ Not Found\n");
   }
   //fflush(stdout);
   return 0;
 }
 int a = fork();
 if(!a){
   execvp(parsed[0],parsed);
 }
 int p, status;
 p = wait(&status);

 free(parsed);
 return 0;
}

int piping(char *input){
  char * pipi = strchr(input,'|');
  char* x = input;
  pipi[0] = 0;
  char * y = pipi + 1;
  char **parse1 = malloc(1024 * sizeof(char *));
  char ** parse2 = malloc(1024 * sizeof(char *));
  parse_args(x,parse1);
  parse_args(y,parse2);
  int pipes[2];
  pipe(pipes);
  int a = fork();
  if(a){
    dup2(pipes[1], 1);
    close(pipes[0]);
    execvp(parse1[0], parse1);

  }
  else {
    dup2(pipes[0], 0);
    close(pipes[1]);
    execvp(parse2[0],parse2);


  }

  free(parse1);
  free(parse2);
  return 0;

}


void trim(char * arg){
  int i = strlen(arg) - 1;
  for(; i > 1; i--){
    if(arg[i] == ' '){
      arg[i] = '\0';
    }
    if(arg[i] != ' '){
      break;
    }
  }
}




int run(char *args){

 char **comline = malloc(1024 * sizeof(char*));

 int command = 0;
 while(args){
   comline[command] = strsep(&args,";");
   run_each(comline[command]);
   command++;
 }

 free(comline);
 return 0;
}

static void signalhandler( int signo){
 char name[100];
 getcwd(name, sizeof(name));
 printf("\nBB-%s$", name);
 fflush(stdout);

}

int main(){



 printf("==============BoroBap=============\n");
 char *args = malloc(1024 * sizeof(args));


 while(1){

   signal(SIGINT, signalhandler);
   char name[100];
   getcwd(name, sizeof(name));
   printf("\nBB-%s$", name);
   fflush(stdout);
   fgets(args,1023, stdin);


   args[strlen(args) - 1] = 0;
   run(args);


 }
 free(args);
 return 0;
}
