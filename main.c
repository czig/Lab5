/*******************************************
 * Author: C2C Caleb Ziegler/CS-39
 * Created: 5 NOV 2013
 * Description: This program runs a simple
 * game on the MSP430 that interfaces with
 * the Geekbox.
 *******************************************/

#include <msp430.h> 
#include "lcd.h"
#include "button.h"
#include "game.h"
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

char buttonflag = 0;
char timerflag = 0;
char count = 0;

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer


    initSPI();
    LCDinit();
    LCDclear();
    configureP1PinAsButton(BIT1 | BIT2 | BIT3 | BIT4);
    position = initPlayer();
    clearPlayer(position);
    updatePlayer(position);
    initTimer();
    __enable_interrupts();


    while(1)
    {
    	if(timerflag ==1)
    	{
    		flag = 0;
    		count ++;
    	}
    	if(count == 4)
    	{
    		MoveCursorLineOne();
    		writeString("Game");
    		MoveCursorLineTwo();
    		writeString("Over");
    	}
    };


}

#pragma vector=TIMER0_A1_Vector
__interrupt void TIMER0_A1_ISR()
{
	TACTL &= ~TAIFG;
	timerflag = 1;
}


#pragma vector=PORT2_VECTOR
__interrupt void Port_2_ISR(void)
{
    P2IFG &= ~(BIT1|BIT2|BIT3|BIT4);                         // clear interrupt flags
    buttonflag = 1;
}
