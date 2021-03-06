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

enum States {Start, Init, ButtonPressed1, OnRelease1, ButtonPressed2} state;

void Tick() {
	switch(state) { //transitions
		case Start:
			state = Init;
			break;
		case Init:
			if((PINA & 0x01) == 0x01 ) {
				state = ButtonPressed1;
			}
			else {
				state = Init;
			}
			break;
		case ButtonPressed1:
			if((PINA & 0x01) == 0x01) {
				state = ButtonPressed1;
			}
			else {
				state = OnRelease1;
			}
			break;
		case OnRelease1:
			if((PINA & 0x01) == 0x01) {
				state = ButtonPressed2;
			}
			else {
				state = OnRelease1;
			}
			break;
		case ButtonPressed2:
			if((PINA & 0x01) == 0x01){
				state = ButtonPressed2;
			}
			else {
				state = Init;
			}
			break;
		default:
			break; 
	}
	switch(state) { //actions
		case Init:
			PORTB = 0x01;
			break;
		case ButtonPressed1:
			PORTB = 0x02;
			break;
		case OnRelease1:
			PORTB = 0x02;
			break;
		case ButtonPressed2:
			PORTB = 0x01;
			break;
		default:
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA = 0x00; PORTA = 0x00;
        DDRB = 0xFF; PORTB = 0x00;
	state = Init; //Inital state
	
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}
