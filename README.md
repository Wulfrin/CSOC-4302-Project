# CSOC-4302-Project

Overview:

miniShell is a simplified UNIX-style shell written in C. It reads user commands, parses them into arguments, searches for the executable in the system PATH, and runs the command in a child process using fork() and execv().

Files:

miniShell.c – Main program logic

miniShell.h – Header file with constants, structures, and required imports

How to Compile:
gcc miniShell.c -o miniShell

How to Run:
./miniShell

Features:

Displays prompt: miniShell>

Reads and parses user commands

Searches PATH for executables

Example Commands:
ls
date

Executes commands using child processes

Supports built-in "exit" command to quit
