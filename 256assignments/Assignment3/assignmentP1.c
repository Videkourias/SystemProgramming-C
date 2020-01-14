#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

void parse(char *buf, char **args){
	int i = 0;
	while(buf[i] != '\0'){ //strips newline character from buffer
		if(buf[i] == '\n') 
			buf[i] = '\0';
		i++;
	}

	while(*buf != '\0'){
		//clears whitespace or newline
        	while((*buf == ' ') || (*buf == '\t'))
	            	*buf++ = '\0';
		

        	*args++ = buf; //adds argument to argument array

		//skips over argument
        	while((*buf != '\0') && (*buf != ' ') && (*buf != '\t'))
            		buf++;

    	}
    	*args = NULL;
}


void execute(char **args){
    	int pid;
    	pid = fork();
    	if(pid == -1){ //fork error
        	printf("Fork error\n"); exit(12);
    	}

    	if(pid == 0){ //child executes argument
       		execvp(*args, args);
		perror(NULL);
    	}
    	else{ //parent waits
        	wait(NULL);
    	}
}



int main(int argc, char *argv[]){
    char buf[1024];
    char *args[64];

    for(;;){
        printf("Command: ");
        if(fgets(buf, 1024, stdin) == NULL){
            printf("\n"); exit(0); 
        }

        parse(buf, args);
        execute(args);
    }
}



