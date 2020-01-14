#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void action(int dummy){
	sleep(1);
}

void child(int *);
void parent(int *, pid_t);

int main(int argc, char *argv[]){
	int fd[2];
	pid_t pid;
	int childRes;
	
	pipe(fd);

	if((pid = fork()) == 0)
		child(fd);
	parent(fd, pid);
}

void parent(int *fd, pid_t pid){
	int childRes, n=0;
	close(fd[1]);

	while(1){
		signal(SIGUSR1, action);

		pause();
		
		read(fd[0], &childRes, sizeof(childRes));

		printf("\nParent: child result: %d\n", childRes);

		if(++n>5){
			printf("Parent: work done, bye bye\n");
			kill(0, SIGTERM);
		}
		printf("Parent: waiting for child\n\n");
		kill(pid, SIGUSR1);

	}	
}

void child(int *fd){
	int value;
	close(fd[0]);

	while(1){
		sleep(1);
		value = random() % 100;
		write(fd[1], &value, sizeof(value));
		printf("Child: waiting for parent\n\n");
		signal(SIGUSR1, action);
		kill(getppid(), SIGUSR1);
		pause();
	}
}
