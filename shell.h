char ** parse_args( char * line);
int run_each(char * command);
int check(char * command);
int run(char *args);
static void signalhandler( int signo);
void trim(char * oboi);
int piping(char *input);
