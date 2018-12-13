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
- wc doesn't seem 100% accurate (ex: from test.sh, bash numbers were 5 5 27, our terminal was 6 6 32)

Function Headers:

```
shell.c --------------------------------------------
/* char **parse_args(char *line, char **buff)
Inputs:  char *line, char **buff
Returns: A pointer to the 2D array containing the parsed args
Seperates the line to be executed
*/

/* int run_commands(char *command)
Inputs:  char *command
Returns: 0 or 1
Runs a specific command (pipe, redirection included)
*/

/*void run(char *args)
Inputs:  char *args
Returns: 0
Parses the args at the ; to be able to run all of those commands
*/

/*void sighandler(int signo)
Inputs:  int signo
Returns: void
*/

/*int main()
Displays shell and allows for input
*/
--------------------------------------------------------

redirect.c --------------------------------------------
/* int check(char* command)
Inputs:  char* command
Returns: 0 or 1
Redirects based on > or <.
*/
--------------------------------------------------------

piping.c -----------------------------------------------
/* int piping(char* input)
Inputs:  char* input
Returns: 0 or 1
Runs pipe commands
*/
--------------------------------------------------------
```
