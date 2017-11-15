/******************************************************
*                  	   tinyEEPROM.c                   *
*                    By Daniel Lytle 				  *
*                  danieljlytle@aol.com				  *
*   An EEPROM controller for reading & writing data   *
*    on ATtiny AVRs. Designed for Pocket Automata.    *
******************************************************/
#include "pocketAutomata.h"

uint8_t readEByte(uint16_t address){
	while(EECR & (1 << EEPE));
	//clears address registers & loads address into it
	EEARH &= ~(0x01);
	EEARH |= (uint8_t) ((address>>8) & (0x01));
	EEARL = (uint8_t) (address & ~(0x10));
	//starts read
	EECR |= (0x01);
	//returns read data
	return EEDR;
}

void writeEByte(uint16_t address, uint8_t byte){
	//waits until last write is done
	while(EECR & (1 << EEPE));
	//sets atomic write mode
	EECR &= ~(0x30);
	//clears address registers & loads address into them
	EEAR = address;
	//puts byte in data register
	EEDR = byte;
	//enables writing and writes
	EECR |= (1<<EEMPE);
	EECR |= (1<<EEPE);
}
