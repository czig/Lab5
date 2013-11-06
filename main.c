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


void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer


    initSPI();
    LCDinit();
    LCDclear();
    position = initPlayer();
    clearPlayer(position);
    updatePlayer(position);

    while(1){};


}
