#include<stdio.h>
#include<unistd.h>


int main(void){
    char buf[210];
    //read(stdin, buf, 200); //stdin is pointer, need integer for read
    read(0,buf,200);
    return 0;
}
