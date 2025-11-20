#include "miniShell.h"

void printPrompt()
{
    printf("miniShell> ");
}

void readCommand(char *commandLine)
{
    printPrompt();
    fgets(commandLine, MAX_LINE_LEN, stdin);
    size_t len = strlen(commandLine);
    if (len > 0 && commandLine[len - 1] == '\n')
    {
        commandLine[len - 1] = '\0';
    }

    // TODO: REMOVE PRINT STATEMENT
    printf("Command Entered: %s\n", commandLine);
}

int parseCommand(char *cLine, Command *cmd)
{
    int argc;
    char **clPtr;

    // Initialization
    clPtr = &cLine;
    argc = 0;
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
    // TODO: Implement lookupPath function
}

int main()
{
    int pid;
    char commandLine[MAX_LINE_LEN];
    char *pathv[MAX_PATH_LEN];
    Command command;

    // Parse PATH variable into dirs[]
    parsePath(pathv);

    // Execution loop
    while (1)
    {
        // Read command line
        readCommand(commandLine);

        // Parse out command and arguments
        parseCommand(commandLine, &command);

        // check in path for command name
        command.name = lookupPath(command.argv, pathv);
        // if command is blank report and continue
        if (command.name == NULL)
        {
            printf("Command not found\n");
            continue;
        }

        // TODO: create child process
    }

    // Success
    return 0;
}