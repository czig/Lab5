/*
 * game.c
 * Author: C2C Caleb Ziegler
 * Date: 5 Nov 2013
 * Description: Implementation for functions in game
 */

#include <msp430.h>
#include "game.h"
#include "lcd.h"
#define UP 1
#define LEFT 2
#define RIGHT 3
#define DOWN 4

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

//void movePlayer(unsigned char position, unsigned char direction)
//{
	//switch (direction) {
		//	case UP:
			//	scrollString(string1,string2);
				//break;
			//case LEFT:
			//	scrollString(string1,string3);
			//	break;
			//case RIGHT:
			//	scrollString(string1,string4);
			//	break;
		//	case DOWN;

			//	break;
	//		}
//}
