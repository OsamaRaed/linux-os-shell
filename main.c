#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

char* myTestStrok(char str[]){

	  char * pch;
	  printf ("Splitting string \"%s\" into tokens:\n",str);
	  pch = strtok (str," ,.-");
	  while (pch != NULL)
	  {
		printf ("%s\n",pch);
		pch = strtok (NULL, " ,.-");
	  }
	  return pch;
}
//            	char ss[] = "aaa bbb ccc ddd";
            	//myTestStrok(ss);

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
            //printf("%s\n",command_token);
            // I just pointed our array element to the start of the small string.
            args[argscounter] = command_token;
            
            // You should update the pointer to the next token, Read about "strtok" in the manual pages.
            //	command_token = ????;
            argscounter++;
        }
        // Don't forget to make your last arg = NULL.
//		args[argscounter] = NULL;
	//	for(int i = 0; i <  10 && args[i] != NULL ;i++){
		//	printf("%s\n",args[i]);
		
		//}
        // Execute your command here, don't forget that you need to pass the full path, (e.g /usr/bin/mkdir)
        // Read about execv in the manula pages (man execv).
		if(strcmp("quit",args[0]) == 0) exit(0);

	    if(fork() == 0){
	    	execvp(args[0],args);
	    } else {
	    	wait(NULL);
	    }

    }
    return 0;
}















