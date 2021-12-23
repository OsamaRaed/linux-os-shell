#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>


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
	char* argv[10];
	parseString(command,argv);
	if(fork() == 0){
		//child
		execvp(argv[0],argv);
	} else {
		//parent
		wait(NULL);
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
		printf("not implemneted\n");
	}
 }
