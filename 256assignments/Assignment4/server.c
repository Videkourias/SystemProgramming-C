#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>

void handle(){
}


//This is the server
int main(int argc, char *argv[]){
	int fd, fd2;
	char ch;

	unlink("../myserver"); //Remove existing named FIFOs
	unlink("../myserver2");

	if(mkfifo("../myserver", 0777) == -1 || mkfifo("../myserver2", 0777) == -1)
		exit(1);

	while(1){
		fprintf(stderr, "Waiting for a client\n");

		fd = open("../myserver", O_RDONLY); //Link up both FIFO pipes
		fd2 = open("../myserver2", O_WRONLY);
		fprintf(stderr, "Got a client: ");



	
		while(read(fd, &ch, 1) == 1){
			fprintf(stderr, "%c", ch);

			if(ch == '\n'){ //If received character is a new line then write confirmation message to pipe
				write(fd2, "I received your message\n", 24);
			}
		}
	}

}
