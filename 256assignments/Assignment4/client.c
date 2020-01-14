#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>

//This is the client
int main(int argc, char *argv[]){
	int fd, fd2;
	char ch;
	char msg[40];

	//Tries to open myserver, hangs until opened
	while((fd = open("../myserver", O_WRONLY)) == -1 || (fd2 = open("../myserver2", O_RDONLY)) == -1){
		fprintf(stderr, "trying to connect\n");
		sleep(1);
	}

	printf("Connected: type in data to be sent\n");
	while((ch = getchar()) != -1){ //-1 is CTRL-D
		write(fd, &ch, 1);
		

		if(ch == '\n'){ //If sent character was a new line, read pipe for confirmation message from server side
			read(fd2, msg, 24);
			printf("%s", msg); //Prints message to stdout
		}
	}
	close(fd);
	close(fd2);
}
