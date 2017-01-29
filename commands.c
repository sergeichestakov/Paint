#include "commands.h"

//Main function that decides what to do based on user input
void doCommand(command c, Board* b){
	switch(c){
		case QUIT: quitCommand(*b);
		case HELP: printHelp();
		printBoard(*b);
		break;
		case ERASE: erase(b);
		printBoard(*b);
		break;
		case WRITE: writeCommand(b);
		printBoard(*b);
		break;
		case ADD: addCommand(b);
		printBoard(*b);
		break;
		case DELETE: deleteCommand(b);
		printBoard(*b);
		break;
		case RESIZE: resizeCommand(b);
		printBoard(*b);
		break;
		case SAVE: saveCommand(*b);
		printBoard(*b);
		break;
		case LOAD: loadCommand(b);
		printBoard(*b);
		default: break;
	}
}

//Reads the character entered by the user and assigns a command based on it or notifies that the user entered an invalid command
command readCommand(Board b){
	char command;
	printf("Enter your command: ");
	scanf(" %c", &command);
	//Prevents invalid input with help and quit command
	if(command == 'h' || command == 'q'){
		if(hasMore()){
			command = 'z';
		}		
	}
	//Decide which command to do based on input
	switch(command){
		case 'q': return QUIT; 
		case 'h': return HELP; 
		case 'w': return WRITE; 
		case 'e': return ERASE; 
		case 'r': return RESIZE; 
		case 'a': return ADD;
		case 'd': return DELETE;
		case 's': return SAVE;
		case 'l': return LOAD;
		default: printf("Unrecognized command. Type h for help.\n");
		clearInput();
		printBoard(b);
		return readCommand(b);
	}			
}

//Command to save the board
void saveCommand(Board b){
	//Scans for name of a file
	char file[50];
	int numArgsRead = scanf(" %s", file);
	//Opens a file with that name
	FILE* fp;
	fp = fopen(file, "w");
	if(!isValidFormatting(numArgsRead, 1) || fp == NULL){
		printf("Improper save command or file could not be created.\n");
		return;
	}
	//Put the number of rows and columns into the beginning of the file in order to know how much to load later
	fprintf(fp,"%d %d", b.numRows, b.numCols);
	//Write array to file one character at a time
	int r,c;
	for(r = 0; r < b.numRows; r++){
		for(c = 0; c < b.numCols; c++){
			fputc(b.board[r][c], fp);
		}
	}
	fclose(fp);
}

void loadCommand(Board* b){
	//Scan name of file
	char file[50];
	int numArgsRead = scanf(" %s", file);
	FILE* fp;
	fp = fopen(file, "r");
	if(!isValidFormatting(numArgsRead, 1) || fp == NULL){
		printf("Failed to open file: %s\n", file);
		return;
	}
	//Resize the array based on the file dimensions written in the beginning of the file
	int numRows, numCols, r, c;
	fscanf(fp, "%d %d", &numRows, &numCols);
	//Resize array
	resizeBoard(b, numRows, numCols);
	//Read every character into the array
	for(r = 0; r < numRows; r++){
		for(c = 0; c < numCols; c++){
			b->board[r][c] = fgetc(fp);
		}
	}
	fclose(fp);
}

//Recieves inputs for the resize command and if valid, resizes the board
void resizeCommand(Board *b){
	int newRows, newCols;
	int numArgsRead = scanf(" %d %d", &newRows, &newCols);
	if(!isValidFormatting(numArgsRead, 2) || newRows < 1 || newCols < 1){
		printf("Improper resize command.\n");
		return;
	}
	resizeBoard(b, newRows, newCols);
}

//Recieves inputs for delete command and if valid, deletes either a row or column depending on user input
void deleteCommand(Board *b){
	char input;
	int num;
	int numArgsRead = scanf(" %c %d", &input, &num);
	if(!isValidFormatting(numArgsRead, 2) || (input != 'r' && input != 'c')){
		error: printf("Improper delete command.\n");
		return;
	}
	//Find out if its a row or column
	if(input == 'r'){
		if(num < 0 || num > b->numRows - 1){
			goto error;
		}
		//Converts row entered into actual row on array
		num = b->numRows - 1 - num;
		deleteRow(b, num);
	} else {
		if(num < 0 || num > b->numCols - 1){
			goto error;
		}
		deleteCol(b, num);
	}
}

//Takes in input for add command and if valid, adds a row or column depending on user input
void addCommand(Board* b){
	char input;
	int num;
	int numArgsRead = scanf(" %c %d", &input, &num);
	if(!isValidFormatting(numArgsRead, 2) || (input != 'r' && input != 'c')){
		error: printf("Improper add command.\n");
		return;
	}
	//Find out if its a row or column
	if(input == 'r'){
		if(num < 0 || num > b->numRows){
			goto error;
		}
		//Convert row
		num = b->numRows - 1 - num;
		//If row is equal to the number of rows add a new one at the top
		if(num < 0){
			num = 0;
		}
		addRow(b, num);
	} else {
		if(num < 0 || num > b->numCols){
			goto error;
		}
		addCol(b, num);
	}
}

//Command to recieve input and draw a line on the board if valid
void writeCommand(Board* b){
	int startRow, startCol, endRow, endCol;
	int numArgsRead = scanf(" %d %d %d %d", &startRow, &startCol, &endRow, &endCol);
	if(!isValidFormatting(numArgsRead, 4) || !validRow(*b, startRow) || !validRow(*b, endRow) || !validCol(*b, startCol) || !validCol(*b, endCol)){
		printf("Improper draw command.\n");
		return;
	}
	//Convert the inputted row into the actual corresponding row in the array
	startRow = b->numRows - 1 - startRow;
	endRow = b->numRows - 1 - endRow;
	//Figure out what kind of line it is 
	Line line = newLine(startRow, startCol, endRow, endCol);
	//Draw line in board
	draw(b, line);
}

//Quit command frees the space on the board and terminates the program
void quitCommand(Board b){
	destroyBoard(b);
	exit(0);
}

//Erases a valid point on the board
void erase(Board* b){
	int row, col;
	int numArgsRead = scanf("%d %d", &row, &col);
	if(!isValidFormatting(numArgsRead, 2) || !validRow(*b, row) || !validCol(*b, col)){
		printf("Improper erase command.\n");
		return;
	}
	//Convert row
	row = b->numRows - 1 - row;
	//Erase
	b->board[row][col] = '*';
}

//Help function shows list of possible commands and their corresponding letters to input
void printHelp(){
	printf("Commands:\n");
	printf("Help: h\n");
	printf("Quit: q\n");
	printf("Draw line: w row_start col_start row_end col_end\n");
	printf("Resize: r num_rows num_cols\n");
	printf("Add row or column: a [r | c] pos\n");
	printf("Delete row or column: d [r | c] pos\n");
	printf("Erase: e row col\n");
	printf("Save: s file_name\n");
	printf("Load: l file_name\n");
}
