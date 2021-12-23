#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>






void runShell(char* command){
	if(fork() == 0){
		//child
		if (strcmp("environ",args[0]) == 0) execvp("env",args);
		else execvp(args[0],args);
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
    		runShell();
    	}
		fclose(fp);
	} else {
		
		
		
		
	}
 }
