# BoroBap Shell
Hasif Ahmed Adil Gondal Per 10

Features:
- Redirection with single > or < work
- Forks and executes commands 
- Parses multiple commands with ;
- Single pipe functionality is there

Attempted:
- To ignore extra spaces when using ls or cd (works for cd but only allows for one extra space for ls)
- Allow for spacing when running redirection or pipe (didn't work yet but I have an idea on how to do it)
- Multipe pipes (unclear) and multiple redirection
- To implement >> and << 

Bugs:
- pipes and redirects cannot be run with spaces
  DOES NOT WORK: cat hi.txt > bye.txt
  WORKS: cat hi.txt>bye.txt
- exit sometimes takes multiple attempts to close shell
- after incorrect commands the error message may be repeated untl cd out of directory and back into it

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
