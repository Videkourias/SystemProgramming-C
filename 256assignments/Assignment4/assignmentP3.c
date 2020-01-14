#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<signal.h>
#include<unistd.h>
#include<fcntl.h>	
#include<ctype.h>


void handle(){
} 


int main(){
	pid_t pid;
	char ch;

	unlink("../fifo");
	unlink("../fifo2");	


	//Open two FIFOs
	if(mkfifo("../fifo", 0777) == -1 || mkfifo("../fifo2", 0777) == -1){
		perror("fifo error");
		exit(1);
	}



	while(1){
		pid = fork();



		if(pid == 0){ //Child Process
			signal(SIGUSR1, handle); //Ignore user defined signal
			int fd1 = open("../fifo", O_RDONLY);
			int fd2 = open("../fifo2", O_WRONLY);


			pause();
			while(read(fd1, &ch, 1)){
				ch = toupper(ch);
				write(fd2, &ch, 1);

				if(ch == '\0'){ //If done current line, break
					break;
				}
			}
			kill(getppid(), SIGUSR1);
			exit(0);
		}

	
		else{ //Parent Process
			signal(SIGUSR1, handle); //Handle user defined signal
			int fd1 = open("../fifo", O_WRONLY);
			int fd2 = open("../fifo2", O_RDONLY);


			while((ch = getc(stdin)) != '\n'){ //Read input from stdin and write to pipe
				write(fd1, &ch, 1);
			}
			ch = '\0';
			write(fd1, &ch, 1); //Send terminating character

			kill(pid, SIGUSR1);
			pause(); 

			while(read(fd2, &ch, 1) == 1){ //Write new data from pipe to stdout
				fprintf(stderr, "%c", ch);
			}		
			printf("\n");
		}
	}


}
