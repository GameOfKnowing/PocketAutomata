/************************************************************
*                       rule110.h                           *
*                    By Daniel Lytle 						*
*                  danieljlytle@aol.com						*
*            Runs the Rule 110 cellular automation 	        *
*    on binary arrays. Designed for Pocket Automata.        *
************************************************************/
#include "pocketAutomata.h"
#include "tinyEEPROM.h"

void rule110(){
	if ((XDIM > 2) && (YDIM > 2)){
		uint8_t i;
		uint8_t j;
		uint8_t k;
		for(i = 0; i < XDIM; i++){
			for(j = 0; j < YDIM; j++){
				uint8_t result = 0x00; 			
				for(k = 0; k < 8; k++){
					bool A; 
					if (i != 0){
						A = !!((1<<k)&(currentDisplay[i-1][j]));
					}
					else{
						A = true;
					}

					bool C;
					if (i < (XDIM - 1)){
						C = !!((1<<k)&(currentDisplay[i+1][j]));
					}
					else{
						C = true;
					}
					
					bool D;
					if (k < 7){
						D = !!((1<<(k+1))&(currentDisplay[i][j]));
					}
					else if ( j < (YDIM - 1) ){
						D = !!((0x01)&(currentDisplay[i][j+1]));
					}
					else if (j == (YDIM - 1)){
						D = !!(i % 2);
					}

					if(!(A && D && C) && (D || C)){
						result |= (1<<k);
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
}
