/*	Author: kennethalvarez
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description:
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Init, PoundPressed, PoundReleased, WyePressed, WyeReleased, InsidePressed, InsideReleased} state;


void Tick() {
	switch(state) { //transitions
		case Start:
			state = Init;
			break;
		case Init:
			if(((PINA & 0x02) == 0x02) && ((PINA & 0x01) != 0x01) && ((PINA & 0x00) != 0x00) && ((PINA & 0x07) != 0x07)) {
				state = PoundPressed; //FOR UNLOCKING WITH POUND
			}
			else if(((PINA & 0x02) != 0x02) && ((PINA & 0x01) != 0x01) && ((PINA & 0x00) != 0x00) && ((PINA & 0x07) == 0x07)) {
				state = InsidePressed; //FOR UNLOCKING FROM THE INSIDE
			}
			else {
				state = Init;
			}
			break;
		case PoundPressed:
			state = PoundReleased;
			break;
		case PoundReleased:
			if(((PINA & 0x02) != 0x02) && ((PINA & 0x01) == 0x01) && ((PINA & 0x00) != 0x00) && ((PINA & 0x07) != 0x07)) {
				state = WyePressed; //IF WYE IS PRESSED AND NOTHING ELSE IS PRESSED'
			}
			else if(((PINA & 0x02) == 0x02) && ((PINA & 0x01) != 0x01) && ((PINA & 0x00) != 0x00) && ((PINA & 0x07) != 0x07)) {
				state = PoundReleased; //IF # IS STILL BEING HELD DOWN AND NOTHING ELSE IS PRESSED TO MESS UP THE COMBO
			}
			else if(((PINA & 0x00) == 0x00) || ((PINA & 0x07) == 0x07)) {
				state = Init; //IF MESSED UP COMBO
			}
			break;
		case WyePressed:
			state = WyeReleased;
			break;
		case WyeReleased:
			if((PINA & 0x01) == 0x01) {
                                state = WyeReleased; //IF WYE IS STILL PRESSED AND NOTHING ELSE IS PRESSED'
                        }
			else {
				 state = Init;
                        }
			break;
		case InsidePressed:
			state = InsideReleased;
			break;
		case InsideReleased:
			if((PINA & 0x07) == 0x07) {
				state = InsideReleased;
			}
			else {
				state = Init;
			}
			break;
		default:
			break; 
	}

	switch(state) { //actions
		case Start:
			break;
		case Init:
			break;
		case PoundPressed:
			break;
		case PoundReleased:
			break;
		case WyePressed:
			PORTB = 0x01;
			break;
		case WyeReleased:
			break;
		case InsidePressed:
			PORTB = 0x00;;
			break;
		case InsideReleased:
			break;
		default:
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA = 0x00; PORTA = 0x00;
        DDRB = 0xFF; PORTB = 0x00;
	state = Start; //Inital state		

    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}
