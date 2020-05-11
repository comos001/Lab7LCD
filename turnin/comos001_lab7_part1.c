/*	Author: victoromosor
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "io.h"
#include "timer.h"

#endif

//VideoLink: https://drive.google.com/file/d/1ZaM78V85Rx_i8ylIqLQ0vu56IEHsqhoi/view?usp=sharing

enum SM_States {START, INC, DEC, RES } state;
unsigned char cnt = 0x00;
unsigned char val = 0x00;
void TickFct() {
	switch(state) {
		case START:
			if ((PINA & 0x01) == 0x00)
			{
				cnt = 10;
				state = INC;
			}
			else if ((PINA & 0x02) == 0x00)
			{
				cnt = 10;
				state = DEC;
			}
			else if ((PINA & 0x03) == 0x00)
			{
				state = RES;
			}
			else
			{
				state = START;
			}
			break;
		case INC:
			if ((PINA & 0x01) == 0x00)
			{
				state = INC;
			}
			else
			{
				state = START;
			}
			break;
		case DEC:
			if ((PINA & 0x02) == 0x00)
			{
				state = DEC;
			}
			else
			{
				state = START;
			}
			break;
		case RES:
			state = START;
			break;
		default:
			state = START;
			break;
	}

	switch(state) {
		case START:
			break;
		case INC:
			if (cnt == 10)
			{
				if (val < 9)
				{
					val++;
					LCD_ClearScreen();
					LCD_WriteData(val + '0');
				}
				cnt = 0;
			}
			else
			{
				cnt++;
			}
			break;
		case DEC:
			if (cnt == 10)
			{
				if (val > 0)
				{
					val--;
					LCD_ClearScreen();
					LCD_WriteData(val + '0');
				}
				cnt = 0;
			}
			else
			{
				cnt++;
			}
			break;
		case RES:
			val = 0x00;
			LCD_ClearScreen();
			LCD_WriteData(val + '0');
			break;
		default:
			val = 0x00;
			break;
	}

}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	TimerSet(100);
	TimerOn();
	LCD_init();
    /* Insert your solution below */
    while (1) {
while(!TimerFlag);
        	TimerFlag = 0;
		TickFct(); 
   }

    return 1;
}
