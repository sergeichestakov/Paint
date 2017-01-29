#include "line.h"

//Creates a new line based on the inputted positions
Line newLine(int startRow, int startCol, int endRow, int endCol){
	Line l;
	l.startRow = startRow;
	l.startCol = startCol;
	l.endRow = endRow;
	l.endCol = endCol;
	return l;
}

//Draws a valid line based on what kind of line it is, if line is not valid notifies user that it cannot draw it
void draw(Board* b, Line l){
	if(isHoriz(l)){
		drawHoriz(b, l);
	}
	else if(isVert(l)){
		drawVert(b, l);
	}
	else if(isRightDiag(l)){
		drawRightDiag(b, l);
	}
	else if(isLeftDiag(l)){
		drawLeftDiag(b, l);
	}
	else {
		printf("Cannot draw the line as it is not straight.\n");
	}
}

//Draws a vertical line
void drawVert(Board* b, Line l){
	//Character is different for each kind of line
	char line = '|';
	//Start at lowest row and move higher
	int start = l.startRow;
	int end = l.endRow;
	if(l.startRow > l.endRow){
		start = l.endRow;
		end = l.startRow; 
	}
	int c = l.startCol;
	int r;
	for(r = start; r <= end; r++){
		//Intersecting lines are denoted by a +
		if(intersects(b, r, c, line)){
			b->board[r][c] = '+';
			continue;
		}
		//Otherwise convert that character on the board into the specific line character
		b->board[r][c] = line;
	}
}

//Draws a horizontal line
void drawHoriz(Board* b, Line l){
	char line = '-';
	int start = l.startCol;
	int end = l.endCol;
	if(l.startCol > l.endCol){
		start = l.endCol;
		end = l.startCol;
	}
	int r = l.startRow;
	int c;
	for(c = start; c <= end; c++){
		if(intersects(b, r, c, line)){
			b->board[r][c] = '+';
			continue;
		}
		b->board[r][c] = line;
	}
}

//Draws a right diagonal line
void drawRightDiag(Board* b, Line l){
	char line = '/';
	int row = l.startRow;
	int col = l.startCol;
	if(l.endRow > l.startRow){
		row = l.endRow;
		col = l.endCol;
	}
	int dist = abs(l.startRow - l.endRow) + 1;
	int i;
	for(i = 0; i < dist; i++){
		if(intersects(b, row - i, col + i, line)){
			b->board[row - i][col + i] = '+';
			continue;
		}
		b->board[row - i][col + i] = line;
	}
}

//Draws a left diagonal line
void drawLeftDiag(Board* b, Line l){
	char line = '\\';
	int row = l.startRow;
	int col = l.startCol;
	if(l.endRow < l.startRow){
		row = l.endRow;
		col = l.endCol;
	}
	int dist = abs(l.startRow - l.endRow) + 1;
	int i;
	for(i = 0; i < dist; i++){
		if(intersects(b, row + i, col + i, line)){
			b->board[row + i][col + i] = '+';
			continue;
		}
		b->board[row + i][col + i] = line;
	}
}

//Returns whether the line has intersected another line at that point
bool intersects(Board* b, int currRow, int currCol, char lineSegment){
	char spot = b->board[currRow][currCol];
	return spot != '*' && spot != lineSegment;
}

//These functions return what kind of line it is based on the entered positions
bool isVert(Line l){
	return l.startCol == l.endCol;
}

bool isHoriz(Line l){
	return l.startRow == l.endRow;
}

bool isRightDiag(Line l){
	int yDist = l.endRow - l.startRow;
	int xDist = l.endCol - l.startCol;
	return abs(yDist) == abs(xDist) && yDist + xDist == 0;
}

bool isLeftDiag(Line l){
	int yDist = l.endRow - l.startRow;
	int xDist = l.endCol - l.startCol;
	return abs(yDist) == abs(xDist) && yDist + xDist != 0;
}
