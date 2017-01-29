#ifndef LINE_H
	#define LINE_H
	#include "board.h"
	#include <stdbool.h>
	typedef struct Line_struct {
		int startRow, startCol, endRow, endCol;
	} Line;
	Line newLine(int startRow, int startCol, int endRow, int endCol);
	void draw(Board* b, Line l);
	void drawVert(Board* b, Line l);
	void drawHoriz(Board* b, Line l);
	void drawRightDiag(Board* b, Line l);
	void drawLeftDiag(Board* b, Line l);
	bool intersects(Board* b, int currRow, int currCol, char lineSegment);
	bool isVert(Line l);
	bool isHoriz(Line l);
	bool isRightDiag(Line l);
	bool isLeftDiag(Line l);
#endif
