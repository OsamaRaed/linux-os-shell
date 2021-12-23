#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

int chackIORedirection(char* string){
	char *pointer = string;
	while(*pointer != '\0'){
		if(*pointer == '<' && *pointer == '>'){
			return 1;
		}
		pointer++;
	}
	return 0;
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



int main (int argc, char *argv[]){
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
		    if(chackAndOp(command)){
		    	handleAndOp(command);
		    } else {
		    	runShell(command);
		    }
	
		    
		}
}

