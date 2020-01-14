#include<stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) 
{
    int len = 5;    
    if(argc > 1){ //If given argument, run that many times
         len = atoi(argv[1]);
    }



	for(int i=0;i<len;i++){ // loop will run n times (n=5 by default) 
  	   if(fork() == 0) { 
           if(i==0){
               execlp("ls", "ls", "-ls", (char *)0);
           }
           else if(i == 1){
               execlp("ps", "ps", "-ef", (char *)0);
           }
	       printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid()); 
		exit(0); 
	  } 
	} 
	for(int i=0;i<len;i++) // loop will run n times (n=5 by default) 
	       wait(NULL); 
	
} 

