#ifndef _BUTTON_H
#define _BUTTON_H

//
// Configures pin as input with internal pull-up resistor.
//
void configureP2PinAsButton(char pin);

//
// Returns one if button pin is high, zero if button pin is low.
char isP2ButtonReleased(char pin);

//
// Blocks while button pin is low.  Debounces on release.
//
void waitForP2ButtonRelease(char pin);

//
// Returns one if button pin is low, zero if button pin is high.
//
char isP2ButtonPressed(char pin);

//
// Polls one or more buttons for press, returns bit mask of pressed button
//
char pollP2Buttons(char buttonsToPoll[], char numberOfButtonsToPoll);

//
// Delays for 1000 clock cycles.
//
void debounce();

#endif
