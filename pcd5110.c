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
	funcSet(0, 1, 1); //exteded instrution set
	biasSet(4); //sets display bias
	VSet(25); //sets display voltage/contrast
	funcSet(0, 1, 0); 
	dispConfig(4); // 0 - blank, 2 - normal, 1 - all on
}

//draws the full screen
void drawScreen(){
	int i;
	int j;
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
		command |= (0x03);
	}
	if(V){
		command |= (0x02);
	}
	if(H){
		command |= (0x01);
	}
		
	sendByte(false, command);
}

//sets display voltage bias
void biasSet(uint8_t bias){
	if(bias < 8){
		uint8_t command = 16 + bias;
		sendByte(false, command);
	}
}

//sets display voltage
void VSet(uint8_t voltage){
	if(voltage < 128){
		uint8_t command = 128 + voltage;
		sendByte(false, command);
	}
}

//sets display output mode
void dispConfig(uint8_t config){
	if(config < 8){
		uint8_t command = 8 + config;
		sendByte(false, command);
	}
}

//sends a command or data byte to the display controller
void sendByte(bool isData, uint8_t byte){
	
	if(isData){
		PORTB |= (1<<DC); //indicates screen data transfer
	}
	else{ 
		PORTB &= ~(1<<DC); //indicates display command transfer
	}
	int i;
	for(i = 7; i >= 0; i--){
		PORTB &= ~(1<<DO);
		PORTB |= ((byte >> i) & 0x01);
		pulseClock();
	}
}
	
void pulseClock(){
	PORTB |= (1 << SCLK);
	PORTB &= ~(1 << SCLK);
}
