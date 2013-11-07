/*
 * game.c
 * Author: C2C Caleb Ziegler
 * Date: 5 Nov 2013
 * Description: Implementation for functions in game
 */

#include <msp430.h>
#include "game.h"
#include "lcd.h"
#include "button.h"

#define UP 1
#define LEFT 2
#define RIGHT 3
#define DOWN 4
#define TRUE 1
#define FALSE 0
#define GAMEOVER 0
#define PLAYON 1
#define SPACE 0x20
#define ASTERISK 0x2A

char initPlayer()
{
	return 0x80;
}

void clearPlayer(unsigned char position)
{
	writeCommandByte(position);
	writeDataByte(SPACE);
}

void updatePlayer(unsigned char position)
{
	writeCommandByte(position);
	writeDataByte(ASTERISK);
}

unsigned char movePlayer(unsigned char position, unsigned char direction)
{
	clearPlayer(position);
	switch (direction) {
			case UP:
				position &= ~BIT6;
				break;
			case LEFT:
				if ((position & 0x0f) > 0)
				{
					position--;
				}
				break;
			case RIGHT:
				if ((position & 0x0f) < 7)
				{
					position++;
				}
		    	break;
			case DOWN:
				position |= BIT6;
				break;
			}
	updatePlayer(position);
	return position;
}


