/*
 * fsm_manual.c
 *
 *  Created on: Nov 28, 2024
 *      Author: ADMIN
 */

#include "fsm_manual.h"

void fsm_manual_run(){
	switch(status){
	case MAN_RED:
	{
		blinking(RED1);
		updateLedBuffer(mode, redDuration / 100);
		if(isButtonPressed(0) == 1){
			if(isButtonPressed(2) == 0){
						redDuration = tempRed;
					}
			status = MAN_YELLOW;
			mode = 3;
		}
		if(isButtonPressed(1) == 1 && mode == 2){
			redDuration += 100;
			if(redDuration > 9900){
				redDuration = 100;
			}
		}
		break;
	}
	case MAN_YELLOW:
		{
			blinking(YELLOW1);
			updateLedBuffer(mode, yellowDuration / 100);
			}
			if(isButtonPressed(0) == 1){
				if(isButtonPressed(2) == 0){
							yellowDuration = tempYellow;
						}
				status = MAN_GREEN;
				mode = 4;
			}
			if(isButtonPressed(1) == 1 && mode == 3){
				yellowDuration += 100;
				if(yellowDuration > 9900){
					yellowDuration = 100;
				}
			}
			break;
	case MAN_GREEN:
		{
			updateLedBuffer(mode, greenDuration / 100);
			blinking(GREEN1);
			if(isButtonPressed(0) == 1){
				if(isButtonPressed(2) == 0){
							greenDuration = tempGreen;
						}
				if (redDuration == (greenDuration + yellowDuration))
				{
					status = RED1_GREEN2;
					redCounter = redDuration / 100;
					greenCounter = greenDuration / 100;
					yellowCounter = yellowDuration / 100;
					mode = 1;
				}
				else
				{
					status = ERROR;
				}
			}
			if (isButtonPressed(1) == 1 && mode == 4)
			{
				greenDuration += 100;
				if (greenDuration > 9900)
				{
					greenDuration = 100;
				}
			}
			break;
		}
	case ERROR:
		status = RED1_GREEN2;
		redDuration = tempRed;
		yellowDuration = tempYellow;
		greenDuration = tempGreen;
		mode = 1;
		redCounter = redDuration / 100;
		greenCounter = greenDuration / 100;
		yellowCounter = yellowDuration / 100;
	default:
		break;
	}
}


