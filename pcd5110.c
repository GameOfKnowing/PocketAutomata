/*********************************************************
*                  		 pcd5110.c                     	 *
*                    By Daniel Lytle 					 *
*                  danieljlytle@aol.com				 	 *
*  A basic controller for using 5110 displays with the 	 *
*    ATtiny85 over SPI. Designed for Pocket Automata 	 *
*********************************************************/
#include "pocketAutomata.h"

bool data = false;
uint8_t command = 0x00;
uint8_t commandPlace = 7;

//initializes and clears display
void initDisplay(){	

	//enables output compare A interrupt
	TIMSK |= (1<<OCIE0A);
	//toggle 0C0A on compare match & CTC mode
	TCCR0A |= ((1<<COM0A1) | (1<<COM0A0) | (1<<WGM01));
	//prescaler = 0
	TCCR0B |= 0x01;
	//counts to 2
	OCR0A |= 0x02;
	//enables SPI cnt. overflow interrupt, selects Counter0 comp. match
	// USI as clock
	USICR |= (1<<USIOIE) | (1<<USICS0);
	
	funcSet(0, 1, 1);
	biasSet(4); //sets display bias
	VSet(50); //sets display voltage/contrast
	funcSet(0, 1, 0); 
	dispConfig(4); // 0 - blank, 2 - normal, 1 - all on
}

//draws the full screen
void drawScreen(uint8_t newScreen[XDIM][YDIM]){
	int i;
	int j;
	for(i = 0; i < XDIM; i++){
		for(j = 0; j < YDIM; j++){
			currentDisplay[i][j] = newScreen[i][j];
		}
	}
	for (i = 0; i < XDIM; i++) {
		for (j = 0; j < YDIM; j++){
			sendByte(true, currentDisplay[i][j]);
		}
	}
}

//switches one pixel, leaving the rest the same
void switchPixel(uint8_t x, uint8_t y){
	currentDisplay[x][y/8] ^= (1 << (y%8));
	if(x < XDIM){
		uint8_t xCommand = 128 + x;
		uint8_t yCommand = 64 + (y/8);
		//sets memory pointer to correct location
		sendByte(false, xCommand);
		sendByte(false, yCommand);
		//writes new bit value
		sendByte(true, currentDisplay[x][y/8]);
		//sets memory pointer back to 0,0
		sendByte(false, 0x80);
		sendByte(false, 0x40);
	}
}

//returns the current value of 1 pixel
bool getPixel(uint8_t x, uint8_t y){
	if (currentDisplay[x][y/8] & (1 << y%8)){
		return true;
	}
	else{
		return false;
	}
}

//sets display power on/off, entry mode, and instruction set 
void funcSet(uint8_t PD, uint8_t V, uint8_t H){
	uint8_t command = 32;
	if(PD){
		command |= (1 << 2);
	}
	if(V){
		command |= (1 << 1);
	}
	if(H){
		command |= (0b1);
	}
		
	sendByte(false, command);
}

//sets display power bias
void biasSet(uint8_t bias){
	if(bias < 8){
		command = 16 + bias;
		sendByte(false, command);
	}
}

//sets display voltage
void VSet(uint8_t voltage){
	if(voltage < 128){
		command = 128 + voltage;
		sendByte(false, command);
	}
}

//sets display output mode
void dispConfig(uint8_t config){
	if(config < 8){
		command = 8 + config;
		sendByte(false, command);
	}
}

//sends a command or data byte to the display controller
void sendByte(bool isData, uint8_t byte){
	USICR &= ~(1<<USIWM0);
	
	if(isData){
		PORTB |= (1<<DC); //indicates screen data transfer
	}
	else{ 
		PORTB &= ~(1<<DC); //indicates display command transfer
	}
	
	USIDR &= (0x00); //clears data register
	USIDR |= (byte); //loads byte into data register
	USISR |= (1<<USIOIF); //clears counter overflow flag
	USICR |= (1<<USIWM0); //sets 3-wire mode
	SREG |= (0x80); //enables global interrupts
	
	while (SREG & (0x80)) {} //waits until global interrupts have been disabled by USI counter overflow
	USICR &= ~(1<<USIWM0); //turns off USI
	
	//PORTB |= (1<<DO); 
	//_delay_ms(500);
	PORTB &= ~(1<<DO);
	_delay_ms(1001);
	PORTB |= (1<<DO);
	_delay_ms(500);
	PORTB &= ~(1<<DO);
	_delay_ms(501);
	PORTB |= (1<<DO);
	_delay_ms(500);
	PORTB &= ~(1<<DO);
	_delay_ms(501);
	PORTB |= (1<<DO);
	_delay_ms(500);
	PORTB &= ~(1<<DO);
	_delay_ms(501);
	

}

//turns off global interrupts (& therefore USI clock) once a byte has been transmitted
ISR(USI_OVF_vect){
	SREG &= ~(0x80);
}

ISR(TIM0_COMPA_vect){
}
