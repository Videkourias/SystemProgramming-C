#include<stdio.h>
#include<stdlib.h>
#define BUFFSIZE 512

int main(int argc, char *argv[]){
	FILE *fp, *fp2;
	char buffer[BUFFSIZE]; //Buffer for lines


	if ((fp = fopen(argv[1], "r")) == NULL || (fp2 = fopen(argv[2], "w")) == NULL){ //Open files for read/write
		printf("Input file opening error... terminating");
		return 1;
	}

	fseek(fp, 0 ,SEEK_END); //Get file size
	int fileSize = ftell(fp);

	rewind(fp); //Back to start of file


	fseek(fp2, fileSize, SEEK_SET);  //Sets offest to size of file 1
	while(fgets(buffer, BUFFSIZE, fp) != NULL){ //Loops until no more lines to get from file 1
		int numChar = 0; //Number of characters read this line
		
		while(buffer[numChar] != '\n') numChar++; //Find num characters in buffer
		numChar++; //Include \n in len		


		fseek(fp2, -numChar, SEEK_CUR); //Move offset in fp2 to allow for writing
		fputs(buffer, fp2); 		//Write current line
		fseek(fp2, -numChar, SEEK_CUR); //Return beginning of line written
	}


	fclose(fp);
	fclose(fp2);

	return 0;
}
