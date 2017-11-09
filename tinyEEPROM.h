/******************************************************
*                  	   tinyEEPROM.c                   *
*                    By Daniel Lytle 				  *
*                  danieljlytle@aol.com				  *
* Functions for reading & writing data to/from EEPROM *
*    on ATtiny AVRs. Designed for Pocket Automata.    *
******************************************************/

//reads a byte of data from given address in EEPROM
uint8_t readEByte(uint16_t address);

//writes a byte of data to given address in EEPROM
uint8_t writeEByte(uint16_t address, uint8_t byte);