#include<stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *args[]) 
{
	if(argc < 2) return -1;   //if no command line arguments given, return


	for(int i=1; i < argc;){ // loop will run n times 
  		if(fork() == 0) {
			printf("process id of this child: %d\n", getpid());

        		if(i == argc - 1){ //if argument is last in list
				char *arg[] = {args[i], (char *)NULL};
               			execvp(args[i], arg);
			}
           		else{ //if argument is not last in list, or last command has an argument 
				char *arg[] = {args[i], args[i + 1], (char *)NULL}; 
               			execvp(args[i], arg); 
           		}
		}


		i += 2;
		if(i > argc){ //increases past commands arguments, unless last command has no argument
			i--;
		}
		sleep(1); //allows child programs to execute in order, can be removed
	} 
	for(int i=0; i < argc; i++) // loop will run n times 
	       wait(NULL); 
	
} 

