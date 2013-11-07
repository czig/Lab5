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
#define UP 1
#define LEFT 2
#define RIGHT 3
#define DOWN 4
#define TRUE 1
#define FALSE 0
#define GAMEOVER 0
#define PLAYON 1

unsigned char position = 0;
char buttonflag = 0;
char timerflag = 0;
char count = 0;

void initTimer();
void initButtons(char pin);
void clearTimer();
void movePlayerforButtonPush(char buttonToTest);
void testAndRespondToButtonPush(char buttonToTest);

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer


    initSPI();
    LCDinit();
    LCDclear();
    initButtons(BIT1|BIT2|BIT3|BIT4);
    position = initPlayer();
    clearPlayer(position);
    updatePlayer(position);
    initTimer();
    __enable_interrupt();


    while(1)
    {
    	if(timerflag ==1)
    	{
    		timerflag = 0;
    		count ++;
    	}
    	if(count == 4)
    	{
    		MoveCursorLineOne();
    		writeString("Game");
    		MoveCursorLineTwo();
    		writeString("Over");
    	}
    }


}

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

void initButtons(char pin)
{
	configureP2PinAsButton(pin);
	P2IES |= pin;                          // configure interrupt to sense falling edges
	P2IFG &= ~pin;                         // clear P2.1-2.4 interrupt flags
	P2IE |= pin;                           // enable the interrupt for all pins
}

void clearTimer()
{
	count = 0; //Might have to change this later
	TACTL |= TACLR;
}

void movePlayerforButtonPush(char buttonToTest)
{
	switch(buttonToTest)
	{
		case BIT1:
			movePlayer(position,UP);
			break;
		case BIT2:
			movePlayer(position,LEFT);
			break;
		case BIT3:
			movePlayer(position,RIGHT);
			break;
		case BIT4:
			movePlayer(position,DOWN);
	}
}

void testAndRespondToButtonPush(char buttonToTest) //Have to edit this function
{
    if (buttonToTest & P2IFG)
    {
        if (buttonToTest & P2IES)
        {
            movePlayerforButtonPush(buttonToTest);
            clearTimer();
        } else
        {
            debounce();
        }

        P2IES ^= buttonToTest;
        P2IFG &= ~buttonToTest;
    }
}


#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR()
{
	TACTL &= ~TAIFG;
	timerflag = 1;
}


#pragma vector = PORT2_VECTOR
__interrupt void Port_2_ISR(void)
{
    P2IFG &= ~(BIT1|BIT2|BIT3|BIT4);                         // clear interrupt flags
    buttonflag = 1;
}
