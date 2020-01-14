#include<stdio.h>
#define BUFFSIZE 512

int main(int argc, char *argv[]){
	FILE *fp, *fp2;
	char buffer[BUFFSIZE];


	if ((fp = fopen(argv[1], "r")) == NULL || (fp2 = fopen(argv[2], "w")) == NULL){
		printf("Input file opening error... terminating");
		return 1;
	}

	fseek(fp, 0 ,SEEK_END); //Get file size
	int fileSize = ftell(fp);
	rewind(fp);
	
	printf("file size: %d\n", fileSize); //Out file size


	
	while(fgets(buffer, BUFFSIZE, fp) != NULL){ //Loops until no more lines to get
		rewind(fp2); //Returns file 2 pointer to beginning of file  //Moves location in file 2 to start of file 2
		fputs("\n", fp2); //DEBUG?
		rewind(fp2);
		fputs(buffer, fp2); //Write lines in reverse order
		fputs(buffer, stdout); //DEBUG
	}

	fclose(fp);
	fclose(fp2);

	return 0;
}
