/*
 *  * ChessCommand.c
 *
 *  Created on: 24 ����� 2017
 *      Author: ido abulafya
 */
#include "ChessCommand.h"

ChessCommand chessCommandParser(const char* str){
	ChessCommand command;
	command.type = INVALID_LINE_COMMAND;
	int numOfwords = 0;
	char* words[MAX_PLAY_COMMAND+1];
	for(int i = 0; i < MAX_PLAY_COMMAND+1; ++i){ //initialize
		words[i] = NULL;
	}
	command.filePath = NULL;
	if(strcmp(str,"\n") == 0) return command;
	GAME_MESSAGE msg = readMaxWords(words, str, 4, &numOfwords);
	if(msg == GAME_FAILED){  //mallocHandling
		freeArray(words, MAX_PLAY_COMMAND+1);
		command.type = FAILED_COMMAND;
		return command;
	}

	if(msg == GAME_INVALID_ARGUMENT){
		freeArray(words, numOfwords);
		return command;
	}
	if (strcmp(words[0],"move") == 0 && numOfwords == 4 && strcmp(words[2],"to") == 0){
		if(isRepresentLocation(words[1]) && isRepresentLocation(words[3])) {
			command.src = parseLocation(words[1]);
			command.dest = parseLocation(words[3]);
			command.type = MOVE_PIECE_COMMAND;
		}
	}
	else if (strcmp(words[0],"get_moves") == 0 && numOfwords == 2){
		if(isRepresentLocation(words[1])){
			command.src =  parseLocation(words[1]);
			command.type = GET_MOVES_COMMAND;
		}
	}
	else if (strcmp(words[0],"castle") == 0 && numOfwords == 2){
		if(isRepresentLocation(words[1])){
			command.src =  parseLocation(words[1]);
			command.type = CASTLE_COMMAND;
		}
	}
	else if(strcmp(words[0],"undo") == 0 && numOfwords == 1){
		command.type = UNDO_MOVE_COMMAND;
	}
	else if(strcmp(words[0],"save") == 0  && numOfwords == 2){

		command.filePath = (char*) malloc((MAX_LINE + 1)*sizeof(char));

		if(command.filePath == NULL) {
			command.type = FAILED_COMMAND;
			return command;
		}

		strcpy(command.filePath, words[1]);
		command.type = SAVE_COMMAND;
	}
	else if(strcmp(words[0],"reset") == 0 && numOfwords == 1)
		command.type = RESET_COMMAND;
	else if(strcmp(words[0],"quit") == 0 && numOfwords == 1)
		command.type = QUIT_COMMAND;
	else
		command.type = INVALID_LINE_COMMAND;
	freeArray(words, numOfwords);
	return command;
}


