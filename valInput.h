#ifndef VALINPUT_H
	#define VALINPUT_H
	#include "board.h"
	#include <ctype.h>
	#include <stdbool.h>
	#include <string.h>
	bool checkDigit(char* string);
	void validateInput(int argc, char** argv, Board* b);
	void clearInput();
	bool validRow(Board b, int r);
	bool validCol(Board b, int c);
	bool checkArgs(char** argv);
	bool hasMore();
	bool isValidFormatting(int num_args_read, int num_args_needed);
#endif
