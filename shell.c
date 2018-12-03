#include <string.h> //strcmp()
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
char ** parse_args( char * line, char ** buff){

 int counter = 0;
 while(line){
   buff[counter] = strsep(&line, " ");
   counter++;
 }
 return buff;
}

int run_each(char * command){
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
