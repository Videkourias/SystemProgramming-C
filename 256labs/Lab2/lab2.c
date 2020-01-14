#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

int main(int argc, char *argv[]){
	int fd;

	if(argc == 1){
		return 0;
	}

	if((fd = open(argv[1], O_RDONLY)) == -1){
		printf("FILE OPEN ERROR\n");
		return 1;
	}

 	

	return 0;
}
