# BoroBap Shell
Hasif Ahmed Adil Gondal Per 10

Features:
- Redirection works
- Forks and executes commands
- Parses multiple commands with ;
- Single pipe functionality is there
- ignores whitespace

Attempted:
- Multiple pipes
- To implement >> and <<

Bugs:
- Multiple pipes and >> <<

Bugs:


Function Headers:

```
/* char **parse_args(char *line, char **buff)
Inputs:  char *line, char **buff
Returns: A pointer to the 2D array containing the parsed args
Seperates the line to be executed
*/

/* void check(char* command)
Inputs:  char* command
Returns: 0
Redirects based on > or <. Currenty space issues!!!
*/

/* int run_commands(char *command)
Inputs:  char *command
Returns: 0
Runs a specific command (pipe, redirection included)
*/

/* void piping(char* input)
Inputs:  char* input
Returns: 0
Runs pipe commands
*/

/*void trim(char *arg)
Inputs:  char *arg
Returns: void
Attemps to trim out spaces so commands can be run properly
*/

/*void run(char *args)
Inputs:  char *args
Returns: 0
Parses the args at the ; to be able to run all of those commands
*/

/*void sighandler(int signo)
Inputs:  int signo
Returns: void
Checks for the SIGINT and prints shell line everytime enter key is pressed.
*/

/*int main()
Displays shell and allows for input
*/
```
