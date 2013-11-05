//
// game.h
// Author: Caleb Ziegler
// Date: 5 Nov 13
// Description: Header file for game
//
#include <msp430.h>
#ifndef GAME_H_
#define GAME_H_

void initTimer();

void initPlayer ();

void clearPlayer (unsigned char position);

void movePlayer (unsigned char position);



#endif
