/*
Name: Ryan Davis 
ID: 1001982627
*/
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
#define MAX_HISTORY 10         // Max history log

/* FUNCTION PROTOTYPES */
void msh();                                     // Main shell function
void get_input(char *input);                    // Displays prompt and gets user input / (input) - buffer to store input            DONE    
void parse_input(char* input, char** parsed);   // Parse input into tokens / (input) - input string / (parsed) - array of tokens    DONE
void execute_cmd(char** parsed);                // Execute command / (parsed) - array of tokens                                     DONE
void change_directory(char* path);              // Change directory / (path) - directory to change to
void view_history();                            // Display history  
void add_history(char* input);                  // Add command to history
void show_pid_history();                        // Display history of pids
void add_pid_history(int pid);                  // Add pid to history
void list_files();                              // List files in directory

/* GLOBAL VARIABLES */
char* history[MAX_HISTORY]; // Array to store history
int pid_history[MAX_HISTORY]; // Array to store pid history
int history_count = 0;
int pid_count = 0;

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
        add_history(input); // Add input to history
        parse_input(input, parsed); // Parse input into tokens

        if(strlen(input) == 0) // If input is empty
        {
            continue; // Skip to next iteration
        }

        if(strcmp(parsed[0], "exit") == 0) // If user enters exit
        {
            printf("Exiting shell\n");
            break; // Exit shell
        }
        else if(strcmp(parsed[0], "cd") == 0) // If user enters cd
        {
            change_directory(parsed[1]); // Change directory
        }
        else if(strcmp(parsed[0], "history") == 0) // If user enters history
        {
            view_history(); // Display history
        }
        else if(strcmp(parsed[0], "pid") == 0) // If user enters pid
        {
            show_pid_history(); // Display pid history
        }
        else if(strcmp(parsed[0], "ls") == 0) // If user enters ls
        {
            list_files(); // List files in directory
        }
        else
        {
            execute_cmd(parsed); // Execute command
        }

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

/* Execute input command */
void execute_cmd(char** parsed)
{
    pid_t pid = fork();             // Create child process

    if(pid < 0)                     // Fork fails
    {
        printf("Command failed to execute\n");
        return;
    }
    else if(pid == 0)
    {
        if(execvp(parsed[0], parsed) < 0) // Execute command
        {
            printf("Command not found\n");
        }
        exit(0); // Exit child process
    }
    else
    {
        add_pid_history(pid); // Add pid to history
        wait(NULL); // Wait for child process to finish
    }
}


/* Change directory */
void change_directory(char* path)
{
    if(chdir(path) != 0) // Change directory
    {
        printf("Directory not found\n");
    }

    char cwd[1024]; // Buffer to store current working directory
    getcwd(cwd, sizeof(cwd)); // Get current working directory
    // printf("Current working directory: %s\n", cwd); // Display current working directory
}

/* Display command history */
void view_history()
{
    printf("Command history\n");
    // Loop through history
    for(int i = 0; i < history_count; i++)
    {
        printf("%d: %s\n", i, history[i]);
    }
}

/* Add command to history */
void add_history(char* input)
{
    if(history_count < MAX_HISTORY)
    {
        history[history_count] = strdup(input); // Add input to history
        history_count++; // Increment history count
    } else
    {
        free(history[0]); // Free memory
        for(int i = 0; i < MAX_HISTORY; i++)
        {
            history[i - 1] = history[i]; // Shift history
        }
        history[MAX_HISTORY - 1] = strdup(input); // Add input to history
    }
}

/* Display history of pids */
void show_pid_history()
{
    printf("PID history\n");
    
    if(pid_count == 0)
    {
        printf("No PIDs recorded!\n");
        return;
    }

    for (int i = 0; i < pid_count; i++)
    {
        printf("%d: %d\n", i, pid_history[i]);
    }
}

/* Add pid to history */
void add_pid_history(int pid)
{
  if (pid_count < MAX_HISTORY)
  {
    pid_history[pid_count] = pid;
    pid_count++;
  } else
  {
    for(int i = 1; i < MAX_HISTORY; i++)
    {
      pid_history[i - 1] = pid_history[i];
    }
    pid_history[MAX_HISTORY - 1] = pid;
  }
}

void list_files()
{
    pid_t pid = fork();             // Create child process

    if(pid < 0)                     // Fork fails
    {
        printf("Command failed to execute\n");
        return;
    }
    else if(pid == 0)
    {
        char* parsed[MAX_ARGS]; // Array of tokens
        parsed[0] = "ls"; // Set first token to ls
        parsed[1] = NULL; // Set last token to NULL

        if(execvp(parsed[0], parsed) < 0) // Execute command
        {
            printf("Command not found\n");
        }
        exit(0); // Exit child process
    }
    else
    {
        wait(NULL); // Wait for child process to finish
    }
}


