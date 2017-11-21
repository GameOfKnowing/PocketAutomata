/************************************************************
*                       rule110.h                           *
*                    By Daniel Lytle 						*
*                  danieljlytle@aol.com						*
*            Runs the Rule 110 cellular automation 	        *
*    on binary arrays. Designed for Pocket Automata.        *
************************************************************/
#include "pocketAutomata.h"

void rule110(){
		uint8_t i;
		uint8_t j;
		uint8_t k;
		for(i = 0; i < XDIM; i++){
			for(j = 0; j < YDIM; j++){
				uint8_t result = 0x00;	
				for(k = 0; k < 8; k++){
					if ((j == 0) && (k == 0)){
						result = currentDisplay[i][0];
					}
					else{
						//generates rule 110 input A
						bool A;
						if(i > 0){
							if(k > 0){
								A = !!((1 << (k-1)) & currentDisplay[i-1][j]);
							}
							else{
								A = !!(0x80 & currentDisplay[i-1][j-1]);
							}
						}
						else{
							A = false;
						}						
						
						//generates rule 110 input B
						bool B;
						if (k > 0){
							B = !!((1 << (k-1)) & currentDisplay[i][j]);
						}
						else {
							B = !!((0x80) & currentDisplay[i][j-1]);
						}
						
						//generates rule 110 input C
						bool C;
						if( i < XDIM){
							if(k > 0){
								C = !!((1 << (k-1)) & currentDisplay[i+1][j]);
							}
							else{
								C = !!(0x80 & currentDisplay[i+1][j-1]);
							}
						}
						else{
							C = false;
						}
	
						//generates next pixel state
						if(!((A && B) && C) && (B || C)){
							result |= (1 << k);
						}
					}
				}
				writeEByte((i*YDIM) + j, result);
			}
		}
		
		for(i = 0; i < XDIM; i++){	//loads the next step/frame from EEPROM to currentDisplay
			for(j = 0; j < YDIM; j++){
				currentDisplay[i][j] = readEByte((i * YDIM) + j);
			}
		}
}
