/*
 * fsm_automatic.c
 *
 *  Created on: Nov 28, 2024
 *      Author: ADMIN
 */
#include "fsm_automatic.h"

void fsm_init()
{
	redCounter = redDuration / 100;
	greenCounter = greenDuration / 100;
	yellowCounter = yellowDuration / 100;
	mode = 1;
}

void fsm_automatic_run(){
	if (isButtonPressed(0))
		{
			clearAll();
			status = MAN_RED;
			mode = 2;
			tempRed = redDuration;
			tempGreen = greenDuration;
			tempYellow = yellowDuration;
			isButtonPressed(1);
			isButtonPressed(2);
		}
	switch(status){
	case INIT:
	{
		clearAll();
		initButton();
		fsm_init();
		status = RED1_GREEN2;
		break;
	}
	case RED1_GREEN2:
	{
		turnOn(RED1);
		turnOn(GREEN2);
		horizontal = redCounter;
		vertical = greenCounter;
		redCounter--;
		greenCounter--;
		if(greenCounter <= 0 ){
		status = RED1_YELLOW2;
		yellowCounter = yellowDuration/100;
		}

		break;
	}
	case RED1_YELLOW2:
	{
		turnOn(RED1);
		turnOn(YELLOW2);
		horizontal = redCounter;
		vertical = yellowCounter;
		redCounter--;
		yellowCounter--;
		if(redCounter <= 0 ){
		status = GREEN1_RED2;
		redCounter = redDuration / 100;
		greenCounter = greenDuration / 100;
		}

		break;
	}
	case GREEN1_RED2:
		{
			turnOn(GREEN1);
			turnOn(RED2);
			horizontal = greenCounter;
			vertical = redCounter;
			redCounter--;
			greenCounter--;
			if(greenCounter <= 0 ){
			status = YELLOW1_RED2;
			yellowCounter = yellowDuration/100;
			}

			break;
		}
	case YELLOW1_RED2:
		{
			turnOn(YELLOW1);
			turnOn(RED2);
			horizontal = yellowCounter;
			vertical = redCounter;
			redCounter--;
			yellowCounter--;
			if(redCounter <= 0 ){
			status = RED1_GREEN2;
			redCounter = redDuration / 100;
			greenCounter = greenDuration / 100;
			}
			break;
		}
	default:
		break;
	}
	if (mode == 1) {
		updateLedBuffer(horizontal,vertical);
	}
}


