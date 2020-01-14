#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>



void alarmH(){
	printf("Ding!\n");
}


int main(int argc, char *args[]){
	if(argc > 2){ //need command line argument
		return -1;
	}


	pid_t pid = fork();
	if(pid == 0){
		sleep(atoi(args[1])); //sleeps for specified seconds
		kill(getppid(), SIGALRM); //alarm to parent
		exit(0);
	}
	else{
		signal(SIGALRM, alarmH); //handles alarm signal
		pause(); //wait for alarm from child
	}

	printf("done\n");
	
}
