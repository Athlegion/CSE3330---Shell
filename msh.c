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

#define MAX_INPUT_SIZE 255 // Max input size

#define MAX_NUM_ARGUMENTS 5 // Max number of arguments

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
    }
}