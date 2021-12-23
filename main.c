#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>


#define READ 0
#define WRITE 1

//will return bool 0 or 1
bool isInternalCommand(char** command){
	int isInternal = true;
	printf("is internal command %s\n",command[0]);
	if(strcmp("quit",command[0]) == 0) exit(0);
	else if(strcmp("clc",command[0]) == 0){
		isInternal = false;
	    printf("\033[H\033[2J");

	}
	else if(strcmp("cd",command[0]) == 0){
		isInternal = false;
		chdir(command[1]);
	}
	else if(strcmp("help",command[0]) == 0){
		isInternal = false;
		system("bash -c help | more +10");
	}
	else if(strcmp("environ",command[0]) == 0){
		isInternal = false;
		printf("PATH : %s\n", getenv("PATH"));
		
	}
	else if(strcmp("help",command[0]) == 0){
		isInternal = false;
		
	}
	else if(strcmp("pause",command[0]) == 0){
		isInternal = false;
	    while(getchar() != '\n');
	}

	printf("isInternal??%d",isInternal);
}


char* parseString(char * command, char **argv){

    int argc = 0;
    int i = 0;
    char *command_token = strtok(command, " \t\n"); 
    while(command_token){
        argv[i] = command_token;
        argc++;
        command_token = strtok(NULL, " \t\n");
        i++;
    }
    argv[i] = NULL;
    for(int i = 0; i <  10 && argv[i] != NULL ;i++){
		printf("strtok function: %s\n",argv[i]);
	}
}


void runShell(char* command){
	printf("run shell\n");
	char* argv[11];
	parseString(command,argv);
	bool condition = isInternalCommand(argv);
	if(condition){
		printf("is not internal\n");
		if(fork() == 0){
			//child
			execvp(argv[0],argv);
		} else {
			//parent
			wait(NULL);
		}	
	}
}



int main (int argc, char *argv[]){
    if(argc > 1){
    
    	printf("test to open file\n");	
		FILE * fp;
		char * line = NULL;
	    size_t len = 0;
        ssize_t read;
		fp = fopen(argv[1], "r");
		if (fp == NULL){
			printf("fail to open file\n");
			exit(1);
		}
		    
		while ((read = getline(&line, &len, fp)) != -1) {
    		printf("Retrieved line of length %zu:\n", read);
    		printf("%s", line);
    		runShell(line);
    	}
		fclose(fp);

    } else {
    
        char currentPath[1024];
		while (1) {
		    getcwd(currentPath, sizeof(currentPath));
		    printf("%s> ", currentPath);
		    // I've assumed that the max command we will recive is 99 characters.
		    char command[100];
		    
		    // Scanning a string util we face a \n (enter) 
		    scanf ("%[^\n]99s", command);
		    
		    // Consume the last \n so our next scan will wait ;)
		    getchar ();
		    runShell(command);
		    
		}
	}
    return 0;
}

	
















