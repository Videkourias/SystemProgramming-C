/*
A child process closing a file pointer inherited from the parent doesn't 
close the parents file pointer. After the child closes fp in the program below,
the parent process can still access the file.
*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(){

	FILE *fp;
	int status;

	if((fp = fopen("in.txt", "r")) == NULL){ //Open file
		perror("File error...\n");
	}




	int pid = fork(); //Id of child process


	if(pid == -1){ //Fork error
		perror("Fork error...\n");
		exit(1);
	}

	if(pid == 0){ //Is child process
		printf("Child process closes file: %p\n", fp);
		fclose(fp);
		exit(1);
	}
	
	wait(NULL); //wait for child


	char str[30];	//String
	void* ptr = fgets(str, 30, fp); //Will print first line of file if file is accessible
	

	if(ptr!=NULL){ //Tests if read was successful
		printf("File read successfully\nFirst line: %s", str);
	}

	return 0;
}
