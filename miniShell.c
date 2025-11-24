#include "miniShell.h"

void printPrompt()
{
    printf("miniShell> ");
}

void readCommand(char *commandLine)
{
    // Print prompt string to the stdout
    printPrompt();
    // Get user input
    fgets(commandLine, MAX_LINE_LEN, stdin);
    // Get the length of the input string
    size_t len = strlen(commandLine);
    // Remove trailing newline character
    // and put in a null character as the last character
    if (len > 0 && commandLine[len - 1] == '\n')
    {
        commandLine[len - 1] = '\0';
    }
}

int parseCommand(char *cLine, Command *cmd)
{
    /*
     * This function parses the command line string, cLine,
     * into its component parts: command name and arguments.
     * It fills in the Command structure pointed to by cmd.
     */
    int argc;
    char **clPtr;
    clPtr = &cLine;
    argc = 0;

    // Allocate space for argv[]
    cmd->argv[argc] = (char *)malloc(MAX_ARG_LEN);

    // Fill argv[]
    while ((cmd->argv[argc] = strsep(clPtr, WHITESPACE)) != NULL)
    {
        cmd->argv[++argc] = (char *)malloc(MAX_ARG_LEN);
    }

    // Set command name and argc
    cmd->argc = argc - 1;
    cmd->name = (char *)malloc(MAX_ARG_LEN);
    strcpy(cmd->name, cmd->argv[0]);

    return 1;
}

int parsePath(char *dirs[])
{
    /*
     * This function reads the PATH variable for this environment,
     *then builds an array, dirs[], of the directories in PATH.
     */

    char *pathEnvVar;
    char *thePath;

    // builds the dirs[] array with NULL values
    int i;
    for (i = 0; i < MAX_PATHS; i++)
    {
        dirs[i] = NULL;
    }

    // Get the PATH environment variable
    pathEnvVar = (char *)getenv("PATH");

    // Allocate space for copying PATH string
    thePath = (char *)malloc(strlen(pathEnvVar) + 1);
    // Copy PATH string
    strcpy(thePath, pathEnvVar);

    // Parse thePath into dirs[] using ':' as the delimiter
    char *token = strtok(thePath, ":");
    i = 0; // reset index for dirs[]
    while (token != NULL && i < MAX_PATHS)
    {
        // Need to allocate space for each potential path
        dirs[i] = (char *)malloc(strlen(token) + 1);
        strcpy(dirs[i], token);
        token = strtok(NULL, ":");
        i++;
    }

    // Free allocated memory for thePath
    free(thePath);
}

char *lookupPath(char **argv, char **dir)
{
    /*
    This function searches the directories identified by the dir
    argument to if argv[0] (the file name) appears there.
    Allocates a new string, place the fill path name in it, then
    return the string.
    */

    char *result;
    char pName[MAX_PATH_LEN];
    int i;

    // Check to see if file name is already an absolute path
    if (argv[0][0] == '/')
    {
        // It's an absolute path, check if it exists
        if (access(argv[0], F_OK) == 0)
        {
            return strdup(argv[0]);
        }
        else // File doesn't exist
        {
            return NULL;
        }
    }

    // search through the PATH directories
    for (i = 0; dir[i] != NULL; i++)
    {
        // Build the full path name
        snprintf(pName, sizeof(pName), "%s/%s", dir[i], argv[0]);

        // Check if the file exists at this path
        if (access(pName, F_OK) == 0)
        {
            // File found, allocate memory for result and return it
            result = (char *)malloc(strlen(pName) + 1);
            strcpy(result, pName);
            return result;
        }
    }
}

int main()
{

    // Declare variables
    int pid;
    char commandLine[MAX_LINE_LEN];
    char *pathv[MAX_PATH_LEN];
    Command command;

    // Parse PATH variable into dirs[]
    parsePath(pathv);

    // Execution loop
    while (1)
    {
        // Read command line input
        readCommand(commandLine);

        // If command is "exit", then quit
        if (strcmp(commandLine, "exit") == 0)
        {
            break;
        }
        else if (strlen(commandLine) == 0)
        {
            // empty command, reprompt
            continue;
        }

        // Parse out command and arguments
        parseCommand(commandLine, &command);

        // check in path for command name
        command.name = lookupPath(command.argv, pathv);
        // if command is blank report and continue
        if (command.name == NULL)
        {
            printf("\"%s\" command not found\n", command.argv[0]);
            continue; // reset for next command input
        }

        // create child process
        pid = fork();
        if (pid == 0)
        {
            // Child process
            execv(command.name, command.argv);
        }
        else
        {
            // Parent process
            wait(NULL); // Wait for child to finish executing
        }
    }

    // Success
    return 0;
}