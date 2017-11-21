/******************************************************
*                       rule110.c                     *
*                    By Daniel Lytle 				  *
*                  danieljlytle@aol.com				  *
*  Functions for processing the next line in an elem- *
*  entary cellular automata simulation with rule 110. *
*  			   Designed for Pocket Automata.  		  *
******************************************************/
#include "pocketAutomata.h"

void rule110(uint8_t lineNum){
	if (lineNum < 8){
		uint8_t i;
		for(i = 0; i < XDIM; i++){
			bool A; //top left input
			bool B; //top middle input
			bool C; //top right input
			if (lineNum != 0){
				newRow[i] = lastRow[i];
				//generates rule 110 input A
				if(i > 0){
					A = !!((1 << (lineNum - 1)) & lastRow[i-1]);
				}
				else{
					A = false;
				}
				
				//generates rule 110 input B
				B = !!((1 << (lineNum - 1)) & lastRow[i]);
				
				//generates rule 110 input C
				if(i < (XDIM -1)){
					C = !!((1 << (lineNum - 1)) & lastRow[i+1]);
				}
				else{
					C = false;
				}	
			}
			else{ //for the LSB/first row of each byte
				newRow[i] = 0x00;
				//generates rule 110 input A
				if(i > 0){
					A = !!(0x80 & lastRow[i-1]);
				}
				else{
					A = false;
				}
				
				//generates rule 110 input B
				B = !!(0x80 & lastRow[i]);
				
				//generates rule 110 input C
				if(i < (XDIM -1)){
					C = !!(0x80 & lastRow[i+1]);
				}
				else{
					C = false;
				}
			}
			
			//clears prev. pixel state before determining new one; disable to create more organic/ glitchy outputs
			//newRow[i] &= ~(1 << lineNum);
			
			if(!(A && B && C) && (B || C)){
				newRow[i] |= (1 << lineNum);
			}
		}
		for(i = 0; i < XDIM; i++){
			lastRow[i] = newRow[i];
		} 
	}
}
