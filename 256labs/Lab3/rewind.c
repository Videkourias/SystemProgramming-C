#include<stdio.h>
int main(){
	FILE *fp;

	fp=	fopen("test.txt", "w");

	fputs("THIS IS A TEST", fp);

	rewind(fp);

	fputs("[REDACTED]", fp);



	return 0;
}
