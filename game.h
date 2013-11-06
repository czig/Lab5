//
// game.h
// Author: Caleb Ziegler
// Date: 5 Nov 13
// Description: Header file for game
//
#include <msp430.h>
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

void initTimer();

char initPlayer ();

void clearPlayer (unsigned char position);

void updatePlayer (unsigned char position);

void movePlayer (unsigned char position, unsigned char direction);






#endif
