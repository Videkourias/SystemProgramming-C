#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#define BUFFSIZE 65536

int main(int argc, char* argv[]){
	int fd;
	
	void filecopy(int, int);

	if(argc == 1){
		filecopy(STDIN_FILENO,STDOUT_FILENO);
	}
	else{
		while(--argc > 0){
			if((fd = open(*++argv, O_RDONLY)) == -1){
				write(1, "cat: can not open file\n", 23);
				return 1;
			}
			else{
				filecopy(fd, STDOUT_FILENO);
				close(fd);
			}
		}
	}
	return 0;
}

//ifd = Input file descriptor
//ofd = Output file descriptor
void filecopy(int ifd, int ofd){
	ssize_t numRead;
	char buffer[BUFFSIZE];
	
	while((numRead = read(ifd, buffer, BUFFSIZE)) > 0){
		write(ofd, buffer, BUFFSIZE);
	}

}
