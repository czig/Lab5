/*
 * game.c
 * Author: C2C Caleb Ziegler
 * Date: 5 Nov 2013
 * Description: Implementation for functions in game
 */

#include <msp430.h>
#include "game.h"
#include "lcd.h"

void initTimer()
{
	TACTL &= ~(MC1|MC0);
	TACTL |= TACLR;
	TACTL |= TASSEL1;
	TACTL |= ID1|ID0;
	TACTL &= ~TAIFG;
	TACTL |= MC1;
	TACTL |= TAIE:
}

void initPlayer()
{
	position = 0x80;
}

void clearPlayer(unsigned char position)
{
	writeCommandByte(position);
	writeString(" ");
}

void movePlayer(unsigned char position)
{
	writeCommandByte(position);
	writeString("*");
}
