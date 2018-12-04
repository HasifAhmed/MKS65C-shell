# BoroBap Shell
Hasif Ahmed Adil Gondal Per 10

Features:
- Redirection with multiple > or < work
- Forks and executes commands 
- Parses multiple commands with ;
- Single pipe functionality is there

Attempted:
- To ignore extra spaces when using ls or cd (works for cd but only allows for one extra space for ls)
- Allow for spacing when running redirection or pipe (didn't work yet but I have an idea on how to do it)
- Multipe pipes (unclear)

Bugs:
- pipes and redirects cannot be run with spaces 
- exit sometimes takes multiple attempts to close shell
- after incorrect commands the error message may be repeated untl cd out of directory and back into it

Function Headers: 
<code> /* char **parse_args(char *line, char **buff)
Inputs:  char *line, char **buff
Returns: A pointer to the 2D array containing the parsed args
Seperates the line to be executed 
*/
</code>
