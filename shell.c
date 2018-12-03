#include <string.h> //strcmp()
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include "shell.h"
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

        int file = open(redir[1], O_CREAT | O_WRONLY, 0644);

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
  if(strchr(command,'<') || strchr(command, '>')){
    int pid = fork();
    if(!pid){
      check(command);
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
 return 0;
}
