#include <string.h> //strcmp()
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include "shell.h"
#include "redirect.h"
#include "pipes.h"
#include <ctype.h>
#include <errno.h>

/* char **parse_args(char *line, char **buff)
Inputs:  char *line, char **buff
Returns: A pointer to the 2D array containing the parsed args
Seperates the line to be executed
*/
char ** parse_args( char * line){

  char ** buff = calloc(10,sizeof(char *));
  int counter = 0;
  char * temp;
  while(line != NULL && counter < 9){
    temp = strsep(&line, " ");
    if(strcmp(temp,"") ){
      buff[counter] = temp;
      //printf("arr[%d]: %s\n", i, arr[i]);
      counter++;
    }

  }
  //printf("%s\n %s\n",buff[0],buff[1]);
  return buff;
}




/* int run_commands(char *command)
Inputs:  char *command
Returns: 0
Runs a specific command (pipe, redirection included)
*/
int run_each(char * command){
  //trim(command);

  if(strchr(command,'<') || strchr(command, '>')){
    int pid = fork();
    if(!pid){
      check(command);
    }
  /*  else if( pid = -1){
    }
  */ 
    int p, status;
    p = wait(&status);
    return 0;
  }

/*
  if(strchr(command,'|')){
    int pid2 = fork();
    if(!pid2){
      piping(command);
    }
    int p, status;
    p = wait(&status);
    return 0;
  }
*/
 char **parsed = parse_args(command);

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
   
   if( execvp(parsed[0],parsed) < 0){
       perror("Command Failed");
             
       //free(parsed);
     }
   
 }
 int p, status;
 p = wait(&status);

 free(parsed);
 return 0;
}



/*void trim(char *arg)
Inputs:  char *arg
Returns: void
Attemps to trim out spaces so commands can be run properly
*/
/*
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
*/


/*void run(char *args)
Inputs:  char *args
Returns: 0
Parses the args at the ; to be able to run all of those commands
*/
int run(char *args){

 char **comline = malloc(1024 * sizeof(char*));
 
 int command = 0;
 while(args){
   comline[command] = strsep(&args,";");
   if(strcmp(comline[command],
	     "") == 0){
     } else{ 
   run_each(comline[command]);
     }
   command++;
    
 }

 free(comline);
 return 0;
}

/*void sighandler(int signo)
Inputs:  int signo
Returns: void
Checks for the SIGINT and prints shell line everytime enter key is pressed.
*/
static void signalhandler( int signo){
 char name[100];
 getcwd(name, sizeof(name));
 printf("\nBB-%s$", name);
 fflush(stdout);

}


/*int main()
Displays shell and allows for input
*/
int main(){



 printf("==============BoroBap=============\n");
 char *args = malloc(1024 * sizeof(args));


 while(1){

   signal(SIGINT, signalhandler);
   char name[100];
   getcwd(name, sizeof(name));
   //printf("\nBB-%s$", name);
   fflush(stdout);
   fgets(args,1023, stdin);


   args[strlen(args) - 1] = 0;
   run(args);


 }
 free(args);
 return 0;
}
