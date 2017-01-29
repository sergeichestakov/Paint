#ifndef COMMANDS_H
	#define COMMANDS_H
	#include <stdio.h>
	#include "valInput.h"
	#include "board.h"
	#include "line.h"
	typedef enum {QUIT, HELP, WRITE, ERASE, RESIZE, ADD, DELETE, SAVE, LOAD} command;
	command readCommand(Board b);
	void doCommand(command c, Board* b);
	void erase(Board* b);
	void saveCommand(Board b);
	void loadCommand(Board* b);
	void writeCommand(Board* b);
	void deleteCommand(Board *b);
	void resizeCommand(Board *b);
	void addCommand(Board* b);
	void quitCommand(Board b);
	void printHelp();
#endif
	
