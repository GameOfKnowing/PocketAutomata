/************************************************************
*                  //Pocket Automata\\                      *
*                    By Daniel Lytle 						*
*                  danieljlytle@aol.com						*
*  Cellular automata simulator for ATtiny microcontrollers  *
*  					& 5110 displays. 						*
************************************************************/
#include "pocketAutomata.h"
#include "pcd5110.h"
#include "rule110.h"
#include "tinyEEPROM.h"

int main(void) {

	DDRB |= (1<<DO)|(1<<DC)|(1<<SCLK); //sets data out, clock, and DC pins as outputs
	PORTB &= ~(1<<DC); //sets DC to 0

    uint8_t i = 0;
    int8_t j = 0;
    
    //Creates starting configuration with pseudo-random values
    for(i = 0; i < XDIM; i++){
    	for(j = 0; j < YDIM; j++){
    		currentDisplay[i][j] = j;
    	}
    } 
    
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
	PORTB |= (1<<DC);
	_delay_ms(250);
	PORTB &= ~(1<<DC);
	_delay_ms(250);
}
