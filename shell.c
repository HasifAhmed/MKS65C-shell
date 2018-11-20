 #include <string.h>
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
int main(){

  printf("==============BoroBap=============\n");
  char *args = malloc(1024 * sizeof(args));

  while(1){
    printf("\nhasifadil@BB:$");
    fflush(stdout);
    int cpid;
    fgets(args,sizeof(args), stdin);
    args[strlen(args) - 1] = 0;
    char **parse = parse_args(args);
    int a = fork();

    if(!a){
      cpid = getpid();
      execvp(parse[0],parse);
      return 0;
    }
    int p, status;
    p = wait(&status);
  }

}
