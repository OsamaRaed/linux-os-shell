#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>




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
}


char* parseString(char * command, char **argv){

    int argc = 0;
    int i = 0;
    char *command_token = strtok(command, " <>\t\n"); 
    while(command_token){
        argv[i] = command_token;
        argc++;
        command_token = strtok(NULL, " <>\t\n");
        i++;
    }
    argv[i] = NULL;
//    for(int i = 0; i <  10 && argv[i] != NULL ;i++){
//		printf("strtok function: %s\n",argv[i]);
//	}
}

int chackIORedirection(char* string){
	char *pointer = string;
	while(*pointer != '\0'){
		if(*pointer == '<' || *pointer == '>'){
			return 1;
		}
		pointer++;
	}
	return 0;
}

int chackAndOp(char* string){
	char *pointer = string;
	while(*pointer != '\0'){
		if(*pointer == '&' && *(pointer + 1) == ' ' && *(pointer - 1) == ' '){
			return 1;
		}

		pointer++;
	}
	return 0;
}

void runShell(char* command){
	printf("run shell\n");
	char* argv[11];
	parseString(command,argv);
	bool condition = isInternalCommand(argv);
	if(condition){
		printf("is not internal %d\n",condition);
		if(fork() == 0){
			//child
			execvp(argv[0],argv);
		} else {
			//parent
			wait(NULL);
		}	
	}
}

int handleAndOp(char* string){

	char* pointer = string;
	while(*pointer != '\0'){
		if(*pointer == '&'){
			*pointer = '\0';
			runShell(string);
			string = pointer + 2;	
		}
		printf("returned%c \n",*pointer);
		pointer++;
	}
	runShell(string);	
}
void IORedirection(char * command,int input,int output){
	char* argv[3]; 
	parseString(command,argv);
	int stdin_copy = dup(0);
	if (fork() == 0){
		if (input){
			close(0);
		    int fd0 = open(argv[1], O_RDONLY);
		    dup2(fd0, 0);
		    char* a[2];
			a[0] = argv[0];
			a[1] = NULL;
		    execvp(*argv,a);
		    
		} 
		if (output)
		{
		    int fd1;
			if(open(argv[1] , O_RDWR)){
		    	FILE *fp = fopen(argv[1], "ab+");
		    }
		    if(output == 1){
		    	fd1 = open(argv[1] , O_RDWR) ;
		    } else {
		    	fd1 = open(argv[1] , O_RDWR | O_APPEND) ;
		    }
		    dup2(fd1, STDOUT_FILENO);
	    	char* a[2];
			a[0] = argv[0];
			a[1] = NULL;
		    close(fd1);
		    execvp(*argv,a);
		}
				    
	}
	else {
		wait(NULL);
		if(input){
			dup2(stdin_copy, 0);
			close(stdin_copy);
		}
			

	}
}
void handleIORedirection(char * command){
	char *pointer = command;
	while(*pointer != '\0'){
		if(*pointer == '<'){
		
			IORedirection(command,1,0);
			break;
		} 
		else if(*pointer == '>'){
			if(*(pointer + 1) == '>') {
				IORedirection(command,0,2);
			} else {
				IORedirection(command,0,1);
			}
			break;
		} 
		pointer++;
	}
}

void runShellByType(char* command){

	if(chackAndOp(command)){
    	handleAndOp(command);
    } else if (chackIORedirection(command)){
    	handleIORedirection(command);
    } else {
    	runShell(command);
    }

}


void readCommandsfromFile(char ** argv){
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
		runShellByType(line);
	}
	fclose(fp);
}

void startMainShell(){
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
	    runShellByType(command);
	}
}

int main (int argc, char *argv[]){
    if(argc > 1){
		readCommandsfromFile(argv);
    } else {
		startMainShell();
	}
    return 0;
}





