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
int main(){



  printf("==============BoroBap=============\n");
  char *args = malloc(1024 * sizeof(args));

  while(1){
    int a = fork();
    printf("\nhasifadil@BB:$");
      //fflush(stdout);
      char *p,cpid[6];
      sprintf(cpid,"%d",getpid());
      p = cpid;
    printf("%s",p); 
   fgets(args,sizeof(args), stdin);
    args[strlen(args) - 1 ] = 0;
    char **parse = parse_args(args);
    printf("Arg 0:%s",parse[0]);
    printf("%d",strcmp(parse[0],"exit"));

    if(!a){
      if(strcmp(parse[0],"exit") == 0){
        char *ok;
        char line[14] = "kill -9 ";
        strcat(line, p);
        ok = line;
        char ** new_parse = parse_args(ok);

        printf("hey");
        printf("%s",new_parse[2]);
        //execvp(new_parse[0],new_parse);
        return 0;
      }
        execvp(parse[0],parse);
        return 0;
    }
    int p, status;
    p = wait(&status);
  }

}
