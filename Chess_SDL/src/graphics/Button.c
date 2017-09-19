/*
 * Button.c
 *
 *  Created on: 18 ����� 2017
 *      Author: Dolev
 */
#include "Button.h"

Button* buttonCreate(BUTTON_TYPE type,bool isActive, bool isClickable){
	Button* button = (Button*) malloc(sizeof(Button));
	button->activeTexture = NULL;
	button->inactiveTexture = NULL;
	button->nonClickableTexture = NULL;
	if(button == NULL){
		printf("Couldn't create Button struct\n");
		return NULL;
	}
	if((button->rect = typeToRect(type)) == NULL || typeToTexture(button, type) == BUTTON_FAILED){
		buttonDestroy(button);
		return NULL;
	}
	button->type = type;
	button->isActive = isActive;
	button->isClickable = isClickable;
	return button;
}
ButtonMessage buttonArrayCreate(Button** buttons,BUTTON_TYPE* types,bool* isActiveArray,bool* isClickableArray, int size){
	for(int i = 0; i < size; ++i){
		buttons[i] = buttonCreate(types[i],isActiveArray[i],isClickableArray[i]);
		if(buttons[i] == NULL){
			buttonArrayDestroy(buttons, i);
			return BUTTON_FAILED;
		}
	}
	return BUTTON_SUCCESS;
}
void buttonArrayDestroy(Button** buttons,int size){
	if(buttons == NULL) return;
	for(int i = 0; i < size; ++i){
		buttonDestroy(buttons[i]);
		buttons[i] = NULL;
	}
	free(buttons);
}
void buttonDestroy(Button* button){
	if(button == NULL) return;
	if(!button->activeTexture) SDL_DestroyTexture(button->activeTexture);
	if(!button->inactiveTexture) SDL_DestroyTexture(button->inactiveTexture);
	if(!button->nonClickableTexture) SDL_DestroyTexture(button->nonClickableTexture);
	free(button);
	return;
}
Button* copyButton(Button* button){
	return NULL;
}
ButtonMessage activateButton(Button* button){
	if(button == NULL) return BUTTON_FAILED;
	button->isActive = true;
	return BUTTON_SUCCESS;
}
ButtonMessage inactivateButton(Button* button){
	if(button == NULL) return BUTTON_FAILED;
	button->isActive = false;
	return BUTTON_SUCCESS;
}
ButtonMessage drawButton(Button* button,SDL_Renderer* renderer){
	if(button == NULL) return BUTTON_FAILED;
	if(button->isClickable == false)
		if(SDL_RenderCopy(renderer, button->nonClickableTexture, NULL, button->rect) == -1) return BUTTON_FAILED;
	else {
		if(button->isActive)
			if(SDL_RenderCopy(renderer, button->activeTexture, NULL, button->rect) == -1) return BUTTON_FAILED;
		else
			if(SDL_RenderCopy(renderer, button->inactiveTexture, NULL, button->rect) == -1) return BUTTON_FAILED;
	}
	return BUTTON_SUCCESS;
}
ButtonMessage hideButton(Button* button){
	if(button == NULL) return BUTTON_FAILED;
	//	if(button->isActive)
	//		SDL_RenderCopy(button->renderer, button->activeTexture, NULL, button->rect);
	//	else
	//		SDL_RenderCopy(button->renderer, button->inactiveTexture, NULL, button->rect);
	//	SDL_RenderPresent(button->renderer);
	return BUTTON_SUCCESS;
}
Button* whichButtonWasClicked(Button** button, int size, int x, int y){
	for(int i = 0; i < size; ++i){
		if(button[i] == NULL) printf("ERROR in whichButtonWasClicked\n");
		if(isClickOnButton(button[i],x,y) && button[i]->isClickable) return button[i];
	}
	return NULL;
}
bool isClickOnButton(Button* button, int x, int y){
	int leftLimit = button->rect->x;
	int rightLimit = leftLimit + button->rect->w;
	int topLimit = button->rect->y;
	int bottomLimit = topLimit + button->rect->h;
	if ((leftLimit <= x && x <= rightLimit) && (topLimit <= y && y <= bottomLimit)) {
		return true;
	}
	return false;
}
ButtonMessage typeToTexture(Button* button, BUTTON_TYPE type){
	return BUTTON_SUCCESS;
}
SDL_Rect* typeToRect(BUTTON_TYPE type){
	return NULL;
}