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
 
 
 			//}
		    // Execute your command here, don't forget that you need to pass the full path, (e.g /usr/bin/mkdir)
		    // Reprintfad about execv in the manula pages (man execv).
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
			
			if( strcmp("myshell",args[0]) == 0){
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
				//char* a  = teststrtok1(line);				
				fclose(fp);
				
				if(fork() == 0){
					//child
					if (strcmp("environ",args[0]) == 0) execvp("env",args);
					elsquit—Quite execvp(args[0],args);
					
				} else {
					//parent
					wait(NULL);
				}

			} else {
				if(fork() == 0){
					//child
				if (strcmp("environ",args[0]) == 0) execvp("env",args);
				else execvp(args[0],args);
				} else {
					//parent
					wait(NULL);
				}
			}
