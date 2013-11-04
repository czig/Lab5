Lab5
====

Interrupts - "A Simple Game"

This repository includes the files main.c, game.h, game.c, lcd.h, lcd.c, button.h, and button.c, which allow the MSP430 to interface with the Geekbox to implement a simple game. Game.h provides the functions required to implement the game, lcd.h provides the functions necessary to interface with the lcd, and button.h provides the functions required to interface with the buttons. 

Operation of the Game: 

Required Functionality - The game displays an asterisk on the upper left display of the LCD. The player must use buttons 1-4 to move the asterisk to the lower right display of the LCD in under 2 seconds in order to win the game. 

B-functionality - In addition to required functionality, the game uses interrupts to handle the button pushes. 

A-Functionality - In addtion to required and B functionality, the game uses two randomly generated mines that the player must navigate around. If the player hits a mine, they lose and the game is over. The mines are generated in a fashion so that the game is never unwinnnable.
