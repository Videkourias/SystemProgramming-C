#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>

/*
Function that every child process of the main process executes
Input: A string called line, user entered
Output: Returns nothing, prints various information based on passed line
*/
void childFunction(char* line){
	write(1,"I am a child working for my parent\n", 36);
	
	char op; //Arithmetic operation
	int n1, n2; //2 operands
	int result; //Result of operation


	int numScan = sscanf(line, "%d %c %d", &n1, &op, &n2); //tokenization

	//Error checks
	if(numScan != 3){ 
		exit(50); //Incorrect Statment
	}
	else if(op == '/' && n2 == 0){
		exit(100); //Division by zero
	}

	//Arithmetic	
	switch(op){	//Check for operation
		case '+':
			result = n1 + n2;
			break;
		case '-':
			result = n1 - n2;
			break;
		case '/':
			result = n1 / n2;
			break;
		case '*':
			result = n1 * n2;
			break;
		default:
			exit(200); //Invalid operation
	}
	
	char output[50]; 
	sprintf(output, "%d %c %d = %d\n", n1, op, n2, result); //Formats output
	

	int len = 0;
	while(output[len++] != '\n'); //Determines correct write byte length
 
	write(1, output, len); //Outputs formatted output
	
	exit(0); 
}


int main(){
	char buffer[100]; //Buffer for input

	write(1, "This program makes simple arithmetics\n", 38);


	while(1){
		write(1, "Enter an arithmetic statement, eg. 34 + 132> ", 45); 
		read(0, buffer, 100); //Reads user input
		
		int pid = fork();
		int status; //Status of child process on return

		if(pid == -1){
			write(1, "Fork error...\n", 14);
			continue;
		}


		if(pid > 0){ //parent
			write(1, "Created a child to make your operation, waiting\n", 48);
			wait(&status); //Waits for child return



			if(WIFEXITED(status) && WEXITSTATUS(status)!= 0){ //Error status check
				char output[11];
				switch(WEXITSTATUS(status)){
					case 50:
						write(1, "Wrong Statement\n", 16);
						break;
					case 100:
						write(1, "Division by zero\n", 17);
						break;
					case 200:
						write(1, "Wrong operator\n", 15);
						break;
					default:
						write(1, "Unknown error\n", 15);

				}
//				sprintf(output, "Error %d\n", WEXITSTATUS(status));
//				write(1, output, 11);				
			}
		}
		else{ //child
			childFunction(buffer);
		}
	}

	return 0;
}
