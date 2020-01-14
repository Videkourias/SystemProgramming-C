/*This program installs a handler to handle SIGINT and ignores SIGTSTP, it then forks and executes the donothing.c program.
 The parent process then tries to kill the child by sending SIGTSTP, but is ignored. The parent sleeps for 5 seconds, allowing the child
 to print its output 5 times, and then sends SIGINT which aborts the application as the handler has reset to default.*/


#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void sigHandle(){ //handles SIGINT
    printf("crtl-c pressed!\n");
}



int main(){
    	signal(SIGINT, sigHandle); //handle ctrl c
	signal(SIGTSTP, SIG_IGN); //ignore ctrl z
	char *args[] = {"donothing", (char *)NULL};

    	pid_t pid = fork();
	if(pid == 0){
        	if(execv("donothing", args) == -1) //child executes donothing
			perror(NULL);
    	}
    	else{
		kill(pid, SIGTSTP); //tries to kill child           
		sleep(5);
		kill(pid, SIGINT); //tries to interrupt child
        }

}

