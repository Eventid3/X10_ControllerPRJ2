/*
 * X10Controller.cpp
 *
 * Created: 11/1/2023 10:37:57 AM
 * Author : esben
 */ 

#include <avr/io.h>
#include "uart.h"
#include "led.h"
#include "switch.h"
#include "SystemController.h"

int main()
{
	char c;
	
	// Initialize LED port
	initLEDport();
	
	initSwitchPort();
	
	// Initialize UART: Baud = 9600, 8 data bits, No Parity
	initUART(9600,8,0);
	SystemController systemcontroller;
	
	//sendString("X10 System Init!\n\r");
	
	bool swPressed = false;
	
	while (1)
	{
		
		c = readChar();
		
		switch (c)
		{
		case 'a':
		case 'A':
			toggleLED(1);
			break;
		case 'l':
		case 'L':
			toggleLED(0);
			systemcontroller.getTemp();
			break;
		}
		
		
	}
}

