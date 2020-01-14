#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

void parse(char *buf, char **args){
    while(*buf != '\0'){
        while((*buf == ' ') || (*buf == '\t'))
            *buf++ = '\0';

        *args++ = buf;

        while((*buf != '\0') && (*buf != ' ') && (*buf != '\t'))
            buf++;

    }
    *args = NULL;
}


void execute(char **args){
    int pid;
    pid = fork();
    if(pid == -1){
        printf("Fork error\n"); exit(12);
    }

    if(pid == 0){
        execvp(*args, args);
    }
    else{
        wait(NULL);
    }
}



int main(int argc, char *argv[]){
    char buf[1024];
    char *args[64];

    for(;;){
        printf("Command: ");
        if(gets(buf) == NULL){ //fgets(buf, 1024, stdin), need to deal with \n char in
//        if(fgets(buf, 1024, stdin) == NULL){
            printf("\n"); exit(0); //parse function.
        }

/*        int i = 0;
        while(buf[i] != '\0'){
            putc(buf[i++], stdout);
        }    
        i = 0;
*/
        parse(buf, args);
//        while(args[i] != NULL){
//            printf("%s||", args[i++]); 
//        }
        execute(args);
    }
}



