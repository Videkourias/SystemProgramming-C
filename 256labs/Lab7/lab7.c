#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void sigHandle(int sig){ //handles SIGSTP and SIGINT
    if(sig == SIGINT){
        printf("crtl-c pressed!\n");
    }
}





int main(){
    signal(SIGINT, sigHandle);
    signal(20, sigHandle);

    pid_t pid = fork();
    if(pid == 0){ //forks
        execlp("donothing.c", "donothing.c", (char *)0); //child executes donothing
    }
    else{
        for(int i=1; i<=15; i++){
            printf("I am in parent proces.\n");
            kill(pid, SIGINT); //tries to kill child or parent
            sleep(1);
        }
    }
}
