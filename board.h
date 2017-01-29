#ifndef BOARD_H
	#define BOARD_H
	#include <stdio.h>
	#include <stdlib.h>
	typedef struct Board_Struct {
		int numRows;
		int numCols;
		char** board;
	} Board;
	void addRow(Board* b, int row);
	void addCol(Board* b, int col);
	void deleteRow(Board* b, int row);
	void deleteCol(Board* b, int col);
	void resizeBoard(Board* b, int newRows, int newCols);
	void resizeRows(Board* b, int newRows);
	void resizeCols(Board* b, int newCols);
	char* copyRow(char* row, int length);
	char** createBoard(int numRows, int numCols);
	void printBoard(Board b);
	void destroyBoard(Board b);
#endif
