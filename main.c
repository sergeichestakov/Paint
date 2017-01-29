/*
Sergei Chestakov
ECS 30 Final Project
This program simulates an ASCII version of paint where a canvas is created and the user is able to perform several actions on it
Based on which command they enter including writing lines on it, adding rows and columns, resizing the board, erasing a point, and saving/loading a specific canvas
The program runs until the user enters q, or the quit command, otherwise it continues to prompt for and execute commands
*/
#include "commands.h"

int main(int argc, char** argv){
	Board board;
	validateInput(argc, argv, &board);
	command c = readCommand(board);
	while(c != QUIT){
		doCommand(c, &board);
		c = readCommand(board);
	}	
	return 0;
}
