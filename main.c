#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main (int argc, char *argv[]){
    // You should get your current path here.
    char* currentPath = "/home/....";
    while (1) {
        printf ("%s> ", currentPath);
        // I've assumed that the max command we will recive is 99 characters.
        char command[100];
        
        // Scanning a string util we face a \n (enter) 
        scanf ("%[^\n]99s", command);
        
        // Consume the last \n so our next scan will wait ;)
        getchar ();
        
        // I've assumed that the max number of args is 10 + 1 (Last one should be NULL).
        char* args[11];
        
        // Read about "strtok" in the manual pages (man strtok).
        char* command_token = strtok (command, " ");
        
        int argscounter = 0;
        while (command_token != NULL && argscounter < 10) {
            if (argscounter != 0) {
                // You will need to split your string into small strings by replacing the space character by \0 character
            }
            
            // I just pointed our array element to the start of the small string.
            args[argscounter] = command_token;
            
            // You should update the pointer to the next token, Read about "strtok" in the manual pages.
            command_token = ????;
            argscounter ++;
        }
        // Don't forget to make your last arg = NULL.
        
        // Execute your command here, don't forget that you need to pass the full path, (e.g /usr/bin/mkdir)
        // Read about execv in the manula pages (man execv).
    }
    return 0;
}
