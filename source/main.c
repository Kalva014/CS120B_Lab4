/*	Author: kennethalvarez
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: PB0 and PB1 each connect to an LED, and PB0's LED is initially on.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Init, LedPressed1, LedPressed2} state;

void Tick() {
	switch(state) { //transitions
		case Init:
			state = LedPressed1;
			break;
		case LedPressed1:
			if((PINA & 0x01) == 0x01) {
				state = LedPressed2;
			}
			else {
				state = LedPressed1;
			}
			break;
		case LedPressed2:
			if((PINA & 0x01) == 0x01){
				state = LedPressed1;
			}
			else {
				state = LedPressed2;
			}
			break;
		default:
			state = LedPressed1;
			break; 
	}
	switch(state) { //actions
		case Init:
			PORTB = 0x00;
			break;
		case LedPressed1:
			PORTB = 0x01;
			break;
		case LedPressed2:
			PORTB = 0x02;
			break;
		default:
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA = 0x00; PORTA = 0x00;
        DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
    while (1) {
	PORTB = 0x00;
	Tick();
    }
    return 1;
}
