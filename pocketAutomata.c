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
    
    uint8_t i;
    for(i = 0; i < XDIM; i += 1){
    		firstRow[i] = 0x00;
    } 
	firstRow[21] = 0x01;
	firstRow[63] = 0x01;
	firstRow[43] = 0x80;
	firstRow[83] = 0x40;
	
	for(i = 0; i < XDIM; i += 1){
    		lastRow[i] = firstRow[i];
    }
	
	initDisplay();
	drawRow();
	

	uint8_t lineNum = 1;
	uint8_t rowNum = 0;
	
	while(1){
		//resets back to beginning of row until all lines are drawn
		if(lineNum >= 8){
			lineNum = 0;
			rowNum++;
		}
		//resets back to top of screen after each full draw
		if (rowNum >= YDIM){
			lineNum = 1;
			rowNum = 0;
			//for(i = 0; i < XDIM; i += 1){ //resets first row on wrap, disable for ongoing scroll/iteration
				//lastRow[i] = firstRow[i];
			//}
		}
		
		setRow(rowNum);
		blink();
		rule110(lineNum);
		drawRow();
		lineNum++;
	}
}

void blink(){
	PORTB &= ~(1<<DC);
	_delay_ms(REDELAYMS/2);
	PORTB |= (1<<DC);
	_delay_ms(REDELAYMS/2);
}
