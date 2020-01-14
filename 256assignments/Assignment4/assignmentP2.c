#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(int argc, char *args[]){
	int fd[2]; 
	pid_t pid; 
	char *cmd = args[1]; //command to be executed

	//Create a pipe
	if(pipe(fd) == -1)
		perror("pipe error");

	//Fork program
	if((pid = fork()) == -1)
		perror("fork error");
	

	//Child
	if(pid == 0){
		close(fd[0]); //Closes read end

		dup2(fd[1], 1); //Changes stdout to print to pipe		
		
		if(execvp(*args, ++args) == -1)
			perror("command execution error");		
		exit(3);
	}

	//Parent
	else{
		FILE *fp;
		int size = 0; //Number of bytes read/to read
		char c;

		close(fd[1]); //Closes write end

		wait(NULL); //Wait for child to terminate

		fp = fopen("result.txt", "w");		
		
		while((read(fd[0], &c, 1)) > 0){
			size++;
			fwrite(&c, 1, 1, fp);			
		}
		printf("the result of %s was written to result.txt with %d bytes\n", cmd, size);
		
	}

}
