/*
 * game.c
 * Author: C2C Caleb Ziegler
 * Date: 5 Nov 2013
 * Description: Implementation for functions in game
 */

#include <msp430.h>
#include "game.h"
#include "lcd.h"
#ifndef GAME_H_
#define GAME_H_
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

void testAndRespondToButtonPush(char buttonToTest)
{
    if (buttonToTest & P1IFG)
    {
        if (buttonToTest & P1IES)
        {
            movePlayerInResponseToButtonPush(buttonToTest);
            clearTimer();
        } else
        {
            debounce();
        }

        P1IES ^= buttonToTest;
        P1IFG &= ~buttonToTest;
    }
}
