#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
int other(void);
  
int main(void){
    int i=0;
    char line[100]="Hello, my name No-Name\n";
    while(line[i] != '\0'){
        putchar(line[i++]);
        sleep(1);
    }
    other();
    return 0;
}
//outputs all at once ~23 seconds after execution



int other(void){
    int i = 0;
    char line[100]="Hello, my name No-Name\n";
    while(line[i]!= '\0'){
        putc(line[i++], stderr);
        sleep(1);
    }    

    return 0;
}
//outputs characters one by one, 1 second inbetween each output
