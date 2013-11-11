Lab5
====

Interrupts - "A Simple Game"

This repository includes the files main.c, game.h, game.c, lcd.h, lcd.c, button.h, and button.c, which allow the MSP430 to interface with the Geekbox to implement a simple game. Game.h provides the functions required to implement the game, lcd.h provides the functions necessary to interface with the lcd, and button.h provides the functions required to interface with the buttons. The functions requiring the use of global variables are included in main.c

##Operation of the Game: 

 - Required Functionality - The game displays an asterisk on the upper left display of the LCD. The player must use buttons 1-4 to move the asterisk to the lower right display of the LCD in under 2 seconds in order to win the game. The top button corresponds to UP, the next button corresponds to LEFT, the next button corresponds to RIGHT, and the bottom button corresponds to DOWN. Once the end game condition has been reached and the LCD reads "Game Over" or "You Win", a single button push will start the game over again.

 - B-functionality - In addition to required functionality, the game uses interrupts to handle the button pushes.

##Functions: 

All functions pertaining to the game are shown below. Functions pertaining to the buttons and lcd are shown in button.h and lcd.h respectively.

```
void initTimer();
```
 - Configures Timer_A to count up and overflow, which triggers the interrupt, every 0.5 seconds.

```
void initButtons();
```
 - Enables communication with the buttons on the geekbox. Calls a function from button.h then configures the buttons to work with interrupts.

```
char initPlayer ();
```
 - Sets position to starting position of 0x80

```
void clearPlayer (unsigned char position);
```
 - Writes a space (blank) to the current position

```
void updatePlayer (unsigned char position);
```
 - Writes an asterisk to the current position

```
unsigned char movePlayer (unsigned char position, unsigned char direction);
```
 - Implements the game logic for a button push. Updates position based on current position and a button push.

```
void clearTimer();
```
 - Simply resets the timer by reseting the count variable and clearing TAR (TAR is register that holds current count of Timer_A and TACLR clears it).

```
void movePlayerforButtonPush(char buttonToTest);
```
 - Moves player up if button 1 is pressed, moves player left if button 2 is pressed, moves player right if button 3 is pressed, and moves player down if button 4 is pressed.

```
void testAndRespondToButtonPush(char buttonToTest);
```
 - If buttonToTest is same as the button that triggered the interrupt and the interrupt was triggered on the falling edge, move player (asterisk) to new location.

```
void Start_Over(char buttonToTest);
```
 - If game has reached end state and a button press occurs, clear LCD, set player to the start, clear Timer_A, and restart game.

##Documentation

 - C2C Mossing was a huge help on helping me accomplish this laboratory exercise. He helped me get all the way to B-functionality by explaining how the functions are supposed to work and walking me through the syntax. He was a huge help in figuring out how to implement the interrupts, the syntax to move the player, some of the game logic, and formatting the code. More specific documentation is included with commits. 

 - C2C Stefan Baron Von Vietinghoff-Scheel helped me with the game logic for the buttons. Again, more specific documentation with commits.

 - Captain Branchflower helped me troubleshoot my B-functionality code. He helped me fix the executable code in main.c by adding delays, disabling interrupts, and enabling interrupts. Also, he helped me fix a big problem with my interrupts by realizing that functions have to be inside the interrupt subroutine instead of just passing a true or false out of the interrupt through the use of a variable (the interrupt kept being called by trying to pass the variable, but this was fixed by using functions to reset the interrupt). Again, more specific documentation is include in commits. 

##Licensing

 - Anyone is free to use and modify this code for any reason as long as it is documented. 