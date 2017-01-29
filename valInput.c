#include "valInput.h"

//Returns whether an inputted string is a digit or not
bool checkDigit(char* string){
	int len = strlen(string);
	int c;
	for(c = 0; c < len; c++){
		if(c == 0 && string[c] == '-'){
			continue;
		}
		if(!isdigit(string[c])){
			return false;
		}
	}
	return true;
}

//Returns whether the number of arguments read is equal to the amount required and eats up all non-white space after 
bool isValidFormatting(int num_args_read, int num_args_needed){
	char new_line = '\n';
	bool is_valid = true; //assume the format is correct
	if(num_args_read != num_args_needed){ //didn't fill in all the format specifiers
		is_valid = false;//format is not correct
	}
	do{
		scanf("%c", &new_line); //read the next character from the standard input
		if(!isspace(new_line)){ //if it isn't white space
			is_valid = false; //extra stuff there so format isn't valid
		}
	}while(new_line != '\n'); //keep reading characters until you reach the new line character
	return is_valid;
}

bool hasMore(){
	char n;
	do{
		scanf("%c", &n);
		if(!isspace(n)){
			return true;
		}
	} while(n != '\n');
	return false;
}

void clearInput(){
	char n;
	do{
		scanf("%c", &n);
	} while(n != '\n');
}

//This function checks to make sure the command line is valid and creates/prints the board based on the input
void validateInput(int argc, char** argv, Board* b){
	int numCols, numRows;
	//Default board is 10x10
	if(argc == 1){
		numRows = 10;
		numCols = 10;
	}
	//Optional command line arguments are the number of rows and columns of the board
	else if(argc == 3){
		if(checkArgs(argv)){
			numRows = atoi(argv[1]);
			numCols = atoi(argv[2]);
		} else {
			numRows = 10;
			numCols = 10;
		}
	}
	//If input is wrong then notify user and make default board
	else{
		printf("Wrong number of command line arguements entered.\n");
		printf("Usage: ./paint.out [num_rows num_cols]\n");
		printf("Making default board of 10 X 10.\n");
		numRows = 10;
		numCols = 10;
	}
	//Initialize the board
	b->numRows = numRows;
	b->numCols = numCols;
	b->board = createBoard(numRows, numCols);
	//Print
	printBoard(*b);
}

bool validRow(Board b, int r){
	return r >= 0 && r < b.numRows;
}

bool validCol(Board b, int c){
	return c >= 0 && c < b.numCols;
}

//Check to make sure the optional command line arguments are positive integers to create a valid board, otherwise create default board
bool checkArgs(char** argv){
	if(!checkDigit(argv[1])){
		printf("The number of rows is not an integer.\n");
		printf("Making default board of 10 X 10.\n");
		return false;
	}
	if(!checkDigit(argv[2])){
		printf("The number of columns is not an integer.\n");
		printf("Making default board of 10 X 10.\n");
		return false;
	}
	int numRows = atoi(argv[1]);
	int numCols = atoi(argv[2]);
	if(numRows < 1){
		printf("The number of rows is less than 1.\n");
		printf("Making default board of 10 X 10.\n");
		return false;
	}
	if(numCols < 1){
		printf("The number of columns is less than 1.\n");
		printf("Making default board of 10 X 10.\n");	
		return false;
	}
	return true;
}
