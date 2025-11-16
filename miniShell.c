/*
 * This is a very minimal shell. It finds an executable in the
 * PATH, then loads it and executes it (using execv). Since
 * it uses "." (dot) as a seperator, it cannot handle file
 * names like "minishell.h"
 * 
 * The focus on this exercise is to use fork, PATH variables,
 * and execv. This code can be extended by doing the exercise at
 * the end of Chapter 9.
 */

#include "miniShell.h"

char *lookupPath(char **, char **);
int parseCommand(char *, struct command_t *);
int parsePath(char **);
void printPrompt();
void readCommand(char *);
...

int main() 
{
    /* Shell initialization */
    printf("Welcome to miniShell!\n");
    ...
    parsePath(pathv); /* Get directory paths from PATH */

    while (true)
    {
        printPrompt(); /* Display prompt */

        /* Read the command line and parse it */
        readCommand(commandLine);
        ...
        parseCommand(commandLine, &command);
        ...

        /* Get the full pathname for the file */
        command.name = lookupPath(command.argv, pathv);
        if (command.name == NULL)
        {
            /* Report error */
            continue;
        }

        /* Create child and execute the command */
        ...

        /* Wait for the child to terminate */
        ...
    }
    
    /* Shell termination */
    return EXIT_SUCCESS;
    
}

void printPrompt()
{
	/* build the prompt string to have the machine name,
	 * current directory, or other desired information
 	 */
	 promptString = ...;
	 printf("%s ", promptString);
}

void readCommand(char *buffer)
{
	/* This code uses any set of I/O functions, such as those in
	 * the stdio library to read the entire command line into
	 * the buffer. This implementation is greatly simplified,
	 * but it does the job.
	 */
	gets(buffer);
}

int parsePath(char *dirs[])
{
	/* This function reads the PATH variable for this 
	 * environment, then builds an array, dirs[], of the
 	 * directories in PATH
	 */
	  char *pathEnvVar;
	  char *thePath;
	
	  for(int i = 0; i < MAX_ARGS; i++)
	  {
		dirs[i] = NULL;
	  }

	  pathEnvVar = (char *) getenv("PATH");
	  thePath = (char *) malloc(strlen(pathEnvVar) + 1);
	  strcpy(thePath, pathEnvVar);

	/* Loop to parse thePath. Look for a ':'
	 * delimiter between each path name.
	 */

	  ...
}

char *lookupPath(char **argv, char **dir)
{
	/* This function searches the directories identified by the dir
	 * argument to see if argv[0] (the file name) appears there.
	 * Allocate a new string, place the full path name in it, then
	 * return the string.
	 */
	  char *result;
	  char pName[MAX_PATH_LEN];

	// Check to see if fire name is already an absolute path name
	  if (*argv[0] == '/')
	  {
		...
	  }

	// Look in PATH directories
	// Use access() to see if the file is in a dir.
	  for (int i = 0; i < MAX_PATHS; i++)
	  {
		...
	  }

	// File name not found in any path variable
	  fprintf(stderr, "%s: command not found\n", argv[0]);
	  return NULL;
}