/*
 * ChessLoadWin.h
 *
 *  Created on: 18 ����� 2017
 *      Author: Dolev
 */

#ifndef GRAPHICS_CHESSLOADWIN_H_
#define GRAPHICS_CHESSLOADWIN_H_

#include <SDL.h>
#include "SimpleWindow.h"

#define LOAD_NUM_OF_REGULAR_BUTTONS 3
#define LOAD_NUM_OF_SLOTS 5
typedef enum {
	LOAD_SLOT1_EVENT,
	LOAD_SLOT2_EVENT,
	LOAD_SLOT3_EVENT,
	LOAD_SLOT4_EVENT,
	LOAD_SLOT5_EVENT,
	LOAD_BACK_EVENT,
	LOAD_LOAD_EVENT,
	LOAD_EXIT_EVENT,
	LOAD_INVALID_ARGUMENT_EVENT,
	LOAD_NONE_EVENT
} LOAD_EVENT;

typedef struct{
	SimpleWindow* simpleWindow;
	Button** regularButtons;
	Button** slotsButtons;
	int num_of_buttons;
	int num_of_slots;
}LoadWin;

LoadWin* loadWindowCreate();
void loadWindowDraw(LoadWin* loadWin);
void loadWindowDestroy(LoadWin* loadWin);
void loadWindowHide(LoadWin* loadWin);
void loadWindowShow(LoadWin* loadWin);
LOAD_EVENT loadWindowHandleEvent(LoadWin* loadWin, SDL_Event* event);
int scanSlotsInDirectory();

#endif /* GRAPHICS_CHESSLOADWIN_H_ */
