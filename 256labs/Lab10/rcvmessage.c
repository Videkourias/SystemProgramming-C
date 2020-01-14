//**************************************************************************************************************************************************

#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include<stdlib.h>
#include <string.h>
#include<unistd.h>
#include <sys/stat.h>

#define MSGSIZE 63

char *fifo = "fifo";

int main(int argc, char **argv){
	int fd;
	char msgbuf[MSGSIZE + 1];

	if (mkfifo(fifo, 0666) == -1 ){
		if (errno != EEXIST) {
			perror("receiver: mkfifo");
			exit(4);
		}
	}

	if ((fd = open(fifo, O_RDWR)) < 0) {   //note O_RDWD, change it to O_RDONLY?
		perror("fifo open failed");
		exit(5);
	}

	for (;;){

		int num=read(fd, msgbuf, MSGSIZE + 1);
		if (num < 0) {
				perror("message read failed");
				exit(6);
		}
		//including the following when O_RDONLY
		
		if (num == 0) {
				printf("nothing to read or no write end.\n");
				continue;
		} 	
		printf("message received:%s\n", msgbuf);
	}
}


