#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int main(){
	pid_t pid = fork();

	if(pid == 0){ //if child, execute infinite loop
		int i = 0;
		while(1){
			sleep(1);
			printf("%d\n", i++);
		}
	}
	else{
		sleep(5);
		kill(pid, SIGSTOP); //tell child to stop
		sleep(5);
		kill(pid, SIGCONT); //tell child to continue
		sleep(3);
		kill(pid, SIGINT); //interrupt child
	}
}
