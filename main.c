#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>



#define READ 0
#define WRITE 1


void teststrtok(char * string){


    char* args[11];
    // Read about "strtok" in the manual pages (man strtok).
    char* command_token = strtok (string, " ");
    int argscounter = 0;
    //printf("first cm %s \n",command_token);
    char* pch;
    while (command_token != NULL && argscounter < 10) {
        if (argscounter != 0) {
            // You will need to split your string into small strings by replacing the space character by \0 character
        	command_token = strtok(NULL," ");

        }
        //("%s\n",command_token);
        // I just pointed our array element to the start of the small string.
        args[argscounter] = command_token;
        
        // You should update the pointer to the next token, Read about "strtok" in the manual pages.
        //	command_token = ????;
        argscounter++;
    }
    for(int i = 0; i <  10 && args[i] != NULL ;i++){
		printf("strtok function: %s\n",args[i]);
	}
	
	if(fork() == 0){
		printf("fork done");
		//child
		execvp(args[0],args);
	} else {
		printf("child ddone");
		//parent
		wait(NULL);
	}
	printf("ddone");
}

int main (int argc, char *argv[]){
    // You should get your current path here.

    char currentPath[1024];
    while (1) {
        getcwd(currentPath, sizeof(currentPath));
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
        //printf("first cm %s \n",command_token);
        char* pch;
        while (command_token != NULL && argscounter < 10) {
            if (argscounter != 0) {
                // You will need to split your string into small strings by replacing the space character by \0 character
            	command_token = strtok(NULL," ");

            }
            //("%s\n",command_token);
            // I just pointed our array element to the start of the small string.
            args[argscounter] = command_token;
            
            // You should update the pointer to the next token, Read about "strtok" in the manual pages.
            //	command_token = ????;
            argscounter++;
        }
        // Don't forget to make your last arg = NULL.
		args[argscounter] = NULL;
		for(int i = 0; i <  10 && args[i] != NULL ;i++){
			printf("%s\n",args[i]);
		}
		//}
        // Execute your command here, don't forget that you need to pass the full path, (e.g /usr/bin/mkdir)
        // Read about execv in the manula pages (man execv).
		if(strcmp("quit",args[0]) == 0) exit(0);
		if(strcmp("cd",args[0]) == 0)
		{
			if(chdir(args[1]) == -1){
				printf("\n\nerrrrrrrrrrrrrrrrr\n\n\n\n\n");
				continue;
			}  
			
		}

		else if(strcmp("help",args[0]) == 0){
		
			printf("\n\n\n\n\n\n\nwe are here");
			system("bash -c help | more +10");
			continue;
		}
		else if(strcmp("pause",args[0]) == 0){
			char ch;
			while(1){
				ch = fgetc(stdin);
				if(ch==0x0A)
				{
					break;
				}
				ch = getchar();

			}

		}
		
		else if( strcmp("myshell",args[0]) == 0){
	    	printf("test to open file\n");	
			FILE * fp;
		    char * line = NULL;
	        size_t len = 0;
            ssize_t read;
			fp = fopen(args[1], "r");
		    if (fp == NULL){
		    	printf("fail to open file\n");
		    	continue;
		    }
		        
		    while ((read = getline(&line, &len, fp)) != -1) {
        		printf("Retrieved line of length %zu:\n", read);
        		printf("%s", line);
    		}
    		teststrtok(line);
    		
    	fclose(fp);
    	if (line)
        	free(line);
		}
	    else {
			if(fork() == 0){
				//child
			if (strcmp("environ",args[0]) == 0) execvp("env",args);
			else execvp(args[0],args);
			} else {
				//parent
				wait(NULL);
			}
	    }

    }
    return 0;
}

	
















