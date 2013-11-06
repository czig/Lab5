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

#ifndef GAME_H_
#define GAME_H_
f
#define UP 1
#define LEFT 2
#define RIGHT 3
#define DOWN 4
#define TRUE 1
#define FALSE 0
#define GAMEOVER 0
#define PLAYON 1

void initTimer()
{
	TACTL &= ~(MC1|MC0);
	TACTL |= TACLR;
	TACTL |= TASSEL1;
	TACTL |= ID1|ID0;
	TACTL &= ~TAIFG;
	TACTL |= MC1;
	TACTL |= TAIE;
}

char initPlayer()
{
	return 0x80;
}

void clearPlayer(unsigned char position)
{
	writeCommandByte(position);
	writeString(" ");
}

void updatePlayer(unsigned char position)
{
	writeCommandByte(position);
	writeString("*");
}

void movePlayer(unsigned char position, unsigned char direction)
{
	switch (direction) {
			case UP:
				position &= ~BIT6;
				break;
			case LEFT:
				if (position > 0x80)
				{
					position--
				}
				if (position > 0xC0)
				{
					position--
				}
				break;
			case RIGHT:
				if (position < 0x87)
				{
					position++
				}
				if (position < 0xC7)
				{
					position++
				}
		    	break;
			case DOWN;
				position |= BIT6;
				break;
	updatePlayer(position);
			}
}


