/******************************************************
*                  		 pcd5110.c                    *
*                    By Daniel Lytle 				  *
*                  danieljlytle@aol.com				  *
*  Functions for controlling 5110 displays with the   *
*        ATtiny85. Designed for Pocket Automata 	  *
******************************************************/

//initializes and clears display
void initDisplay();

//displays a splash screen
void splashScreen();

//draws the full screen
void drawScreen();

//switches state of one pixel, leaving the rest the same
void switchPixel( uint8_t x, uint8_t y);

//returns the current value of 1 pixel
bool getPixel(uint8_t x, uint8_t y);

//sets the function mode of display
void funcSet(uint8_t PD, uint8_t V, uint8_t H);

//sets display power bias
void biasSet(uint8_t bias);

//sets display voltage
void VSet(uint8_t voltage);

//sets display output mode
void dispConfig(uint8_t config);

//sends a command or data byte to the display controller
void sendByte(bool isData, uint8_t byte);

//pulses SCLK

void pulseClock();
