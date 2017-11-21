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
#include "pcd5110.h"
//#include "tinyEEPROM.h"
#include "rule110.h"

#define DC PB1
#define DO PB0
#define SCLK PB2
#define XDIM 84
#define YDIM 6
#define REDELAYMS 100

uint8_t firstRow[XDIM];
uint8_t lastRow[XDIM];
uint8_t newRow[XDIM];

void blink();
