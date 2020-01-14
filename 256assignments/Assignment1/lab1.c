#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<sys/time.h>


int main(int argc, char *argv[]){
	int fd1, fd2;
	char buffer[1];
	long int n1;

	long int loops = 0;
/*
	clock_t start, end; //Clock for CPU time
	struct timeval wallStart, wallEnd; //gettimeofday for wall time
	double cpu_time, wall_time;

	start = clock();
	gettimeofday(&wallStart, NULL);
*/
	if(((fd1 = open(argv[1], O_RDONLY)) == -1) || ((fd2 = 
	  open(argv[2],O_CREAT|O_WRONLY|O_TRUNC, 0700)) == -1)){
		perror("file problem ");
		exit(1);
	}

	while((n1 = read(fd1, buffer, 1)) > 0){
		loops++;
		if(write(fd2,buffer,n1) != n1){
			perror("writing problem ");
			exit(3);
		}

	}

	if(n1 == -1){
		perror("reading problem ");
		exit(2);
	}
	close(fd2);

	printf("# of loops: %d\n", loops);

/*	
	end = clock();
	gettimeofday(&wallEnd, NULL);

	cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
	wall_time = (wallEnd.tv_usec - wallStart.tv_usec);

	
	printf("CPU time: %f\n", cpu_time);
	printf("Wall time: %f\n", (double)(wall_time/1000000));
*/	
	exit(0);
}
