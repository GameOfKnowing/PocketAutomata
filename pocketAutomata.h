/******************************************************
*                    pocketAutomata.h                 *
*                    By Daniel Lytle 				  *
*                  danieljlytle@aol.com				  *
*  Libraries, constants, & shared arrays for cellular *
*         automation simulations on the ATtiny85.     *
******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DC PB0
#define DO PB1
#define SCLK PB2
#define XDIM 84
#define YDIM 6

uint8_t currentDisplay[XDIM][YDIM];

void blink();
