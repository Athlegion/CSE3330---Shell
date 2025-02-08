// Ryan Davis 
// 1001982627
// Create own shell similar to bash

// Libraries used
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>

#define MAX_INPUT_SIZE 255  // Max input size
#define MAX_ARGS 10         // Max number of arguments
#define MAX_HISTORY         // Max history log

/* FUNCTION PROTOTYPES */
void msh();                     
void get_input(char *input);                    // Displays prompt and gets user input / (input) - buffer to store input
void parse_input(char* input, char** parsed);   // Parse input into tokens / (input) - input string / (parsed) - array of tokens
void execute_cmd(char** parsed);                // Execute command / (parsed) - array of tokens
void change_directory(char* path);              // Change directory / (path) - directory to change to
void view_history();                            // Display history  
void add_history(char* input);                  // Add command to history
void show_pid_history();                        // Display history of pids
void add_pid_history(int pid);                  // Add pid to history

/* GLOBAL VARIABLES */

int main()
{
    msh(); // Call msh function
    return 0; // Return 0
}

void msh()
{
    char * command_str = (char *) malloc(MAX_INPUT_SIZE); // Allocate memory for command string

    while (1)
    {
        printf("msh> "); // Prompt for user input

        // Read command from user - wait for user input, if user input is NULL, exit
        while(!fgets(command_str, MAX_INPUT_SIZE, stdin));

        // If command given is supported, call the function and display the output

        if (strcmp(command_str, "exit\n") == 0)
        {
          exit(0);                                      // Exit the shell
        }

        // If cd command is given, change directory
        else if (strcmp(command_str, "cd\n") == 0)
        {
            chdir(getenv("HOME"));                              // Change directory to home directory
        }
    }
}

