/*	Author: kennethalvarez
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description:
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Init, ButtonPressed1, OnRelease1, ButtonPressed2, OnRelease2, Reset} state;


void Tick() {
	switch(state) { //transitions
		case Start:
			state = Init;
			break;
		case Init:
			if((PINA & 0x01) == 0x01) {
				state = ButtonPressed1;
			}
			else if((PINA & 0x02) == 0x02) {
				state = ButtonPressed2;
			}
			else {
				state = Init;
			}
				
			if((PINA & 0x03) == 0x03) { //RESET STATEMENT MIGHT BE WRONG
				state = Reset;
			}
			break;
		case ButtonPressed1:
			state = OnRelease1;

			if((PINA & 0x03) == 0x03) { //RESET STATEMENT MIGHT BE WRONG
                                state = Reset;
                        }
			break;
		case OnRelease1:
			if((PINA & 0x01) == 0x01) {
				state = OnRelease1;
			}
			else {
				state = Init;
			}
			break;
		case ButtonPressed2:
			state = OnRelease2;

			if((PINA & 0x03) == 0x03) { //RESET STATEMENT MIGHT BE WRONG
       				state = Reset;
                        }
			break;
		case OnRelease2:
			if((PINA & 0x02) == 0x02) { //If button is held down then stay in release
				state = OnRelease2;
			}
			else {
				state = Init;
			}
			break;
		case Reset:
			state = Init;
			break;
		default:
			break; 
	}
	switch(state) { //actions
		case Start:
			break;
		case Init:
			break;
		case ButtonPressed1:
			if(PINC < 9) {
				PORTC = PINC +  0x01;
			}
			break;
		case OnRelease1:
			break;
		case ButtonPressed2:
			if(PINC > 0) {
				PORTC = PINC - 0x01;
			}
			break;
		case OnRelease2:
			break;
		case Reset:
			PORTC = 0x00;
			break;
		default:
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA = 0x00; PORTA = 0x00;
        DDRC = 0xFF; PORTC = 0x07;
	state = Start; //Inital state		

    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}
