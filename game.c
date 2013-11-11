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
#define SPACE 0x20
#define ASTERISK 0x2A

void initTimer()
{
	TACTL &= ~(MC1|MC0);                  //Stop timer
	TACTL |= TACLR;                       //clear TAR
	TACTL |= TASSEL1;                     //Select SMCLK (1MHz)
	TACTL |= ID1|ID0;                     //Divide clock by 8 (now 125kHz)
	TACTL &= ~TAIFG;                      //clear interrupt flag
	TACTL |= MC1;                         //Continuous count mode
	TACTL |= TAIE;                        //enable interrupt
}

void initButtons()
{
	configureP2PinAsButton(BIT1|BIT2|BIT3|BIT4);
	P2IES |= (BIT1|BIT2|BIT3|BIT4);                          //configure interrupt to sense falling edges
	P2IFG &= ~(BIT1|BIT2|BIT3|BIT4);                       //clear P2.1-2.4 interrupt flags
	P2IE |= BIT1|BIT2|BIT3|BIT4;                           //enable the interrupt for all pins
}

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
				position &= ~BIT6; //If player presses button corresponding to UP, clear BIT6 to turn the upper nibble from a hex C to a hex 8 (or from hex 8 to hex 8)
				break;
			case LEFT:
				if ((position & 0x0f) > 0) //If lower nibble is greater than zero (not off screen to left), move position to left
				{
					position--;
				}
				break;
			case RIGHT:
				if ((position & 0x0f) < 7) //If lower nibble is less than 7 (not off screen to right), move position to right
				{
					position++;
				}
		    	break;
			case DOWN:
				position |= BIT6; //If player presses button corresponding to DOWN, set BIT6 to turn the upper nibble from a hex 8 to a hex C (or from hex C to hex C)
				break;
			}
	updatePlayer(position);
	return position;
}


