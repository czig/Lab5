#include <msp430.h> 
#include "lcd.h"
#include "button.h"
#include "game.h"
/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
	return 0;
}
