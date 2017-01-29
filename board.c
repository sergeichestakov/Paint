//This is the board class to create, print, modify and get rid of the char double pointer board in the board object
#include "board.h"

//Creates a rectangular board of any size given the number of columns and rows
char** createBoard(int numRows, int numCols){
	char** board = (char**)malloc(numRows * sizeof(char*));
	int i, j;
	for(i = 0; i < numRows; ++i){
		board[i] = (char*)malloc(numCols * sizeof(char));
		//Fill each space with an asterisk to signal an empty space
		for(j = 0; j < numCols; ++j){
			board[i][j] = '*';
		}
	}
	return board;
}

void resizeBoard(Board* b, int newRows, int newCols){
	resizeRows(b, newRows);
	resizeCols(b, newCols);
}

//Resizes the rows of the board
void resizeRows(Board* b, int newRows){
	//Resize rows
	int r;
	if(newRows > b->numRows){
		//Allocate more space 
		b->board = (char**)realloc(b->board, newRows * sizeof(char*));
		int diffRows = newRows - b->numRows;
		//Move every existing row down the difference between newRows and old
		for(r = newRows - 1; r >= diffRows; r--){
			b->board[r] = copyRow(b->board[r - diffRows], b->numCols);
		}
		//Make every new row at the top empty
		for(r = 0; r < diffRows; r++){
			int c;
			for(c = 0; c < b->numCols; c++){
				b->board[r] = realloc(b->board[r], b->numCols * sizeof(char));
				b->board[r][c] = '*';
			}
		}
	}
	if(newRows < b->numRows){
		//Transfer rows over
		int diffRows = b->numRows - newRows;
		for(r = 0; r < newRows; r++){
			b->board[r] = copyRow(b->board[r + diffRows], b->numCols);
		}
		//Free rows to remove
		for(r = newRows; r < b->numRows; r++){
			free(b->board[r]);
		}
		//Reallocate
		b->board = (char**)realloc(b->board, newRows * sizeof(char*));
	}
	b->numRows = newRows;
}

//Resize the number of columns in each row of the board
void resizeCols(Board* b, int newCols){
	int r;
	for(r = 0; r < b->numRows; r++){
		//5th row is the error
		b->board[r] = (char*)realloc(b->board[r], newCols * sizeof(char));
		if(newCols > b->numCols){
			int c;
			//Empty new columns
			for(c = b->numCols; c < newCols; c++){
				b->board[r][c] = '*';
			}
		}
	}
	b->numCols = newCols;
}

//Used to make the board BEAUTIFUL
int numDigits(int num){
	int count = 0;
	while(num != 0){
		num /= 10;
		count++;
	}
	return count;
}

//Prints a pretty pretty board
void printBoard(Board b){
	int i, j;
	for(i = 0; i < b.numRows; ++i){
		//Print the row number
		printf("%*d ", numDigits(b.numRows - 1), b.numRows - 1 - i);
		//Spacing depending on row to make it look good
		//Prints every single character of the array
		for (j = 0; j < b.numCols; ++j){
			printf("%c ", b.board[i][j]);
		}
		printf("\n");
	}
	printf(" ");
	if(b.numRows > 10){
		printf(" ");
	}
	//Print the column number
	for(i = 0; i < b.numCols; ++i){
		printf(" %d", i);
	}
	printf("\n");
}

//Delete a row on the board
void deleteRow(Board* b, int row){
	//Move every row down one
	int r;
	for(r = row + 1; r < b->numRows; r++){
		b->board[r - 1] = copyRow(b->board[r], b->numCols);
	}
	b->numRows--;
	//Realloc
	b->board = (char**)realloc(b->board, b->numRows * sizeof(char*));
}

//Delete a column in the board
void deleteCol(Board* b, int col){
	b->numCols--;
	int r;
	//Move each column after the deleted row down one in each row
	for(r = 0; r < b->numRows; r++){
		int c;
		for(c = col; c < b->numCols; c++){
			b->board[r][c] = b->board[r][c + 1];
		}
		b->board[r] = (char*)realloc(b->board[r], b->numCols * sizeof(char));
	}
}

//Adds a row to the board
void addRow(Board* b, int row){
	//Reallocate space in the board
	b->numRows++;
	b->board = (char**)realloc(b->board, b->numRows * sizeof(char*));
	//Move every row over 1
	int r;
	for(r = b->numRows - 1; r > row; r--){
		b->board[r] = copyRow(b->board[r - 1], b->numCols);
	}
	int c;
	//Each new row is empty
	for(c = 0; c < b->numCols; c++){
		if(row == 0){
			b->board[row][c] = '*';
		} else {
			b->board[row + 1][c] = '*';
		}	
	}
}

//Returns a copy of a row in order to avoid issues
char* copyRow(char* row, int length){
	char* newRow = (char*)malloc(length * sizeof(char));
	int i;
	for(i = 0; i < length; i++){
		newRow[i] = row[i];
	}
	return newRow;
}

//Adds a column to the board
void addCol(Board* b, int col){
	b->numCols++;
	int r;
	//For every row
	for(r = 0; r < b->numRows; r++){
		//Allocate more space
		b->board[r] = (char*)realloc(b->board[r], b->numCols * sizeof(char*));
		//Move columns over
		int c;
		for(c = b->numCols - 1; c > col; c--){
			b->board[r][c] = b->board[r][c - 1];
		}
		//Make the column empty
		b->board[r][col] = '*';
	}
}

//Free the board 
void destroyBoard(Board b){
	int i;
	//Free each row first as they are all char pointers
	for(i = 0; i < b.numRows; ++i){
		free(b.board[i]);
	}
	free(b.board);
}
