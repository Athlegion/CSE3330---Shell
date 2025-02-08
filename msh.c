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
void msh();                                     // Main shell function
void get_input(char *input);                    // Displays prompt and gets user input / (input) - buffer to store input            DONE    
void parse_input(char* input, char** parsed);   // Parse input into tokens / (input) - input string / (parsed) - array of tokens    DONE
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
    char input[MAX_INPUT_SIZE]; // Buffer to store input
    char *parsed[MAX_ARGS];     // Array of tokens
    //char * command_str = (char *) malloc(MAX_INPUT_SIZE); // Allocate memory for command string

    while (1)
    {
        get_input(input); // Get user input

    }
}

/* Get user input */
void get_input(char *input)
{
    printf("msh> "); // Display prompt
    fgets(input, MAX_INPUT_SIZE, stdin); 

    // Remove newline character from input
    input[strcspn(input, "\n")] = '\0'; 
}

/* Parse input into tokens */
void parse_input(char* input, char** parsed)
{
    int i = 0; 
    char* token = strtok(input, " "); 

    // Loop through input and tokenize
    while(token != NULL && i < MAX_ARGS - 1)
    {
        parsed[i++] = token; // Store token in parsed array
        token = strtok(NULL, " "); // Get next token
    }
    parsed[i] = NULL; // Set last element to NULL
}

