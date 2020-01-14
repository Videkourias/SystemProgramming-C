#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<errno.h>

void handle(){
	printf("Caught SIGPIPE\n");

}


int main(){
	int fd[2]; //Declare pipe
	signal(SIGPIPE, handle); //Handle SIGPIPE signal


	pipe(fd); //Create PIPE


	close(fd[0]);
	int ret = write(fd[1], "error\n", 6); //Try to write to pipe with closed read end


	printf("Returns is: %d\n", ret);

	if(errno == EPIPE){ //Test errno
		printf("errno is set to EPIPE\n");
	}
}
