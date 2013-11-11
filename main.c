/*******************************************
 * Author: C2C Caleb Ziegler/CS-39
 * Created: 5 NOV 2013
 * Description: This program runs a simple
 * game on the MSP430 that interfaces with
 * the Geekbox. The coding style is a little
 * unorthodox in this file because some
 * functions are declared and implemented in
 * main.c instead of game.c. I discussed this
 * with C2C Mossing and he explained to me
 * that declaring functions in main.c prevents
 * errors with interrupts and ensures that global
 * variables work correctly.
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

unsigned char position = 0;
char direction = 0;
char buttonflag = 0;
char timerflag = 0;
char count = 0;
char gameover = FALSE;

/*****************************************
 * Main.c embedded header
 ******************************************/

//Simply resets the timer by reseting the count
//variable and clearing TAR (TAR is register that
//holds current count of Timer_A and TACLR clears it).
void clearTimer();

//Moves player up if button 1 is pressed, moves player
//left if button 2 is pressed, moves player right if button
//3 is pressed, and moves player down if button 4 is pressed.
void movePlayerforButtonPush(char buttonToTest);

//If buttonToTest is same as the button that triggered
//the interrupt and the interrupt was triggered on the falling
//edge, move player (asterisk) to new location.
void testAndRespondToButtonPush(char buttonToTest);

//If game has reached end state and a button press occurs, clear LCD,
//set player to the start, clear Timer_A, and restart game.
void Start_Over(char buttonToTest);

/**********************************
 * Main.c Executable code
 **********************************/

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    //Initializes the game
    initSPI();
    LCDinit();
    LCDclear();
    initButtons();
    position = initPlayer();
    clearPlayer(position);
    updatePlayer(position);
    initTimer();
    __enable_interrupt();

    while(1)
    {
    	//Count every time Timer_A overflows
    	if (timerflag == 1)
    	{
    		timerflag = 0;
    		count++;
    	}

    	//After 2 seconds (0.5 seconds times four) without moving, game over
    	if(count >= 4)
    	{
    		TACTL &= ~TAIE;  //Disable timer interrupt
    		__disable_interrupt(); //Disable all interrupts so button pushes won't interrupt writing to LCD
    		LCDclear();
    	    gameover = TRUE;
    		MoveCursorLineOne();
    		writeString("Game    ");
    		MoveCursorLineTwo();
    		writeString("Over    ");
    		__enable_interrupt();
    		__delay_cycles(1000);
    		clearTimer();
    		TACTL |= TAIE;  //Enable timer interrupt
    	}

    	//If player makes it to end spot, they win
    	if(position == 0xC7)
    	{
    		TACTL &= ~TAIE;  //Disable timer interrupt
    		__disable_interrupt(); //Disable all interrupts so button pushes won't interrupt writing to LCD
    		LCDclear();
    		gameover = TRUE;
    		MoveCursorLineOne();
    		writeString("You     ");
    		MoveCursorLineTwo();
    		writeString("Win     ");
    		__enable_interrupt();
    		__delay_cycles(1000);
    		clearTimer();
    		TACTL |= TAIE;  //Enable timer interrupt
    	}
    }


}

/*********************************
 * Main.c embedded implementation
 *********************************/

void clearTimer()
{
	count = 0;
	TACTL |= TACLR;          //clear TAR
}

void movePlayerforButtonPush(char buttonToTest)
{
	switch(buttonToTest)
	{
		case BIT1:
			position = movePlayer(position,UP);
			break;
		case BIT2:
			position = movePlayer(position,LEFT);
			break;
		case BIT3:
			position = movePlayer(position,RIGHT);
			break;
		case BIT4:
			position = movePlayer(position,DOWN);
	}
}

void testAndRespondToButtonPush(char buttonToTest)
{
    if (buttonToTest & P2IFG) //If button being tested triggered interrupt, continue on
    {
        if (buttonToTest & P2IES) //If interrupt was triggered on falling edge (good button push), continue to move player
        {
            movePlayerforButtonPush(buttonToTest);
            clearTimer();

        } else  //If interrupt was triggered on rising edge, button release occurred, so debounce
        {
            debounce();
        }

        P2IES ^= buttonToTest;  //Toggle flag to select opposite edge of what occurred earlier (if falling edge, now select rising edge, and vice versa)
        P2IFG &= ~buttonToTest; //Clear interrupt flag so this interrupt is not called again
    }
}

void Start_Over(char buttonToTest)
{
	if (buttonToTest & P2IFG) //Make sure one of the buttons triggered interrupt
	    {
	        if (buttonToTest & P2IES) //If triggered on falling edge, we have a button press, so start game over
	        {
	            gameover = FALSE;
	            LCDclear();
	            position = initPlayer();
	            clearPlayer(position);
	            updatePlayer(position);
	            clearTimer();
	            TACTL |= TAIE;

	        } else //If interrupt was triggered on rising edge, no button press (release of button), so debounce
	        {
	            debounce();
	        }

	        P2IES ^= buttonToTest; //Make flag select opposite edge of what occurred earlier
	        P2IFG &= ~buttonToTest; //Clear interrupt flag to not call this interrupt again
	    }
}

/*********************************
 * Interrupt Code
 *********************************/

//Timer_A interrupt code
#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR()
{
	TACTL &= ~TAIFG;
	timerflag = 1;
}

//Button interrupt code
#pragma vector = PORT2_VECTOR
__interrupt void Port_2_ISR(void)
{
		if(gameover == FALSE)
		{
			//Test all buttons to see what one was pushed if not in end game condition
			testAndRespondToButtonPush(BIT1);
			testAndRespondToButtonPush(BIT2);
			testAndRespondToButtonPush(BIT3);
			testAndRespondToButtonPush(BIT4);
		}
		else
		{
			//Again, test all buttons to see if game should start over when in end game condition
			Start_Over(BIT1);
			Start_Over(BIT2);
			Start_Over(BIT3);
			Start_Over(BIT4);
		}
}
