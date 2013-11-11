//
// game.h
// Author: Caleb Ziegler
// Date: 5 Nov 13
// Description: Header file for game
//
#include <msp430.h>
#include "lcd.h"
#include "button.h"
#ifndef GAME_H_
#define GAME_H_
#define UP 1
#define LEFT 2
#define RIGHT 3
#define DOWN 4
#define TRUE 1
#define FALSE 0

//Configures Timer_A to count up and overflow,
//which triggers the interrupt, every 0.5 seconds.
void initTimer();

//Enables communication with the buttons on the
//geekbox. Calls a function from button.h then
//configures the buttons to work with interrupts.
void initButtons();

//Sets position to starting position of 0x80
char initPlayer ();

//Writes a space (blank) to the current position
void clearPlayer (unsigned char position);

//Writes an asterisk to the current position
void updatePlayer (unsigned char position);

//Implements the game logic for a button push. Updates position based on current position and a button push.
unsigned char movePlayer (unsigned char position, unsigned char direction);


#endif
