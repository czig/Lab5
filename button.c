#include <msp430.h>
#include "button.h"

#define TRUE 1

void configureP2PinAsButton(char pin)
{
    P2DIR &= ~pin;
    P2OUT |= pin;
    P2REN |= pin;
    P2IES |= pin;                          // configure interrupt to sense falling edges
    P2IFG &= ~pin;                         // clear P2.1-2.4 interrupt flags
    P2IE |= pin;                           // enable the interrupt for all pins
}

char isP2ButtonReleased(char pin)
{
    return P2IN & pin;
}

void waitForP2ButtonRelease(char pin)
{
    while (!isP2ButtonReleased(pin)) {}
    debounce();
}

char isP2ButtonPressed(char pin)
{
    return !(P2IN & pin);
}

char pollP2Buttons(char buttonsToPoll[], char numberOfButtonsToPoll)
{
    int i;

    while (TRUE)
    {
        for (i = 0; i < numberOfButtonsToPoll; i++) {
            if (isP1ButtonPressed(buttonsToPoll[i]))
            {
                return buttonsToPoll[i];
            }
        }
    }
}

void debounce()
{
    __delay_cycles(1000);
}
