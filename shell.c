  #include <string.h> //strcmp()
 #include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/wait.h>
char ** parse_args( char * line ){

  char **args = calloc(1, sizeof(char **) );
  char * s1 = line;
  args[0] = calloc(1,sizeof(char*));
  line = strsep(&s1," ");
  args[0] = line;
  int i = 1;
  while(s1!=NULL){
    args[i] = calloc(1,sizeof(char*));
    line = strsep(&s1," ");
    args[i] = line;
    i++;
  }
  args[i] = NULL;
  return args;
}

void run(char *args){
  char **parse = malloc(1024 * sizeof(char *));
  parse = parse_args(args);
	int counter = 0;
	while(args){
        parse[counter] = strsep(&args, ";");
		    //run_commands(parse_args(parse[counter]));
        execvp(parse[0], parse);
        counter++;
	}
}
int main(){



  printf("==============BoroBap=============\n");
  char *args = malloc(1024 * sizeof(args));

  while(1){
    int a = fork();
    printf("\nhasifadil@BB:$");
      //fflush(stdout);
      
    fgets(args,1023, stdin);
    args[strlen(args) - 1 ] = 0;
    //char **parse = parse_args(args);
    run(args);
    
    int p, status;
    p = wait(&status);
  }

}
