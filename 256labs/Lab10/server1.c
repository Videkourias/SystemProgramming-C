// This is the server

#include <wait.h>
#include <fcntl.h> 
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

void child(pid_t client);

int main(int argc, char *argv[]){  
	int fd, status;
	char ch;  
	
	pid_t pid;
    
    unlink("../server");

	if(mkfifo("../server", 0777)){  
		perror("main");
		exit(1);
	}
	
	while(1){
		fprintf(stderr, "Waiting for a client\n");  
		fd = open("../server", O_RDONLY);  
		fprintf(stderr, "Got a client: ");  		

		read(fd, &pid, sizeof(pid_t));

		close(fd);

		fprintf(stderr, "%ld\n", pid);  
		
		if(fork()==0)
			child(pid);
		else
			waitpid(0, &status, WNOHANG);
	}
}


void child(pid_t pid){
	char fifoName[100];  
	char newline = '\n';  
	int fd, i;


	sprintf(fifoName,"../fifo%d", pid);  

	unlink(fifoName);
	
	mkfifo(fifoName, 0777);

	fd = open(fifoName, O_WRONLY);  

	for(i=0; i < 100; i++){
		write(fd, fifoName, strlen(fifoName));  
		write(fd, &newline, 1);
		sleep(1);
	}
	close(fd);  
	unlink(fifoName);  
	exit(0);
}

