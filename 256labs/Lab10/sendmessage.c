//*******************************
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include<stdlib.h>
#include <string.h>
#include<unistd.h>


//sendmessage "message 1 text"  "messgae 2 text"  ...

#define MSGSIZE 63

char *fifo = "fifo";

int main(int argc, char **argv) {
	int fd, j, nwrite;
	char msgbuf[MSGSIZE + 1];

	if (argc < 2)
	{
		fprintf(stderr, "usage: send message1 message 2 ....... \n");
		exit(1);
	}

	if ((fd = open(fifo, O_WRONLY | O_NONBLOCK)) < 0) {  //if delete O-NONBLOCK
		perror("fifo open failed");
		exit(4);
	}

	for (j = 1; j < argc; j++){
		if (strlen(argv[j]) > MSGSIZE)		{
			fprintf(stderr, "message too long %s\n", argv[j]);
			continue;
		}

		strcpy(msgbuf, argv[j]);

		if ((nwrite = write(fd, msgbuf, MSGSIZE + 1)) == -1) {
			perror("message wirte failed");
			exit(5);
		}
	}
	exit(0);
}


