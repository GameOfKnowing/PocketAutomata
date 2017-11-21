/************************************************************
*                  //Pocket Automata\\                      *
*                    By Daniel Lytle 						*
*                  danieljlytle@aol.com						*
*  Cellular automata simulator for ATtiny microcontrollers  *
*  					& 5110 displays. 						*
************************************************************/
#include "pocketAutomata.h"

int main(void) {

	DDRB |= (1<<DO)|(1<<DC)|(1<<SCLK); //sets data out, clock, and DC pins as outputs
	PORTB &= ~(1<<DC); //sets DC to 0
    
    int i;
	int j;
    for(i = 0; i < XDIM; i++){
    	for(j = 0; j < YDIM; j++){
    		currentDisplay[i][j] = 0x00;
    	}
    } 

	currentDisplay[70][3] = 0x80;

	initDisplay();
	drawScreen();

	while(1){
		blink();
		rule110();
		drawScreen();
		_delay_ms(5000);
	}
}

void blink(){
	PORTB &= ~(1<<DC);
	_delay_ms(250);
	PORTB |= (1<<DC);
	_delay_ms(250);
}
