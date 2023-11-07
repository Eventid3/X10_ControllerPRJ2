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
#include "lm751.h"
#include "SystemController.h"

void sendTemp();

int main()
{
	LM75_init();
	initLEDport();
	initSwitchPort();

	char c;
	
	initUART(9600,8,0); // Initialize UART: Baud = 9600, 8 data bits
	sendString("UART init!\n\r");
	
	SystemController systemcontroller;
	sendString("X10 System Init!\n\r");
	
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
			sendTemp();
			break;
		}
	}
}

void sendTemp()
{
	// læs temperaturen i halve grader (int på 49 er 24,5 grader)
	int temp = LM75_temperature(0);
	
	sendInt(temp/2);

	// hvis den sidste bit i tallet er 1 (dvs tallet er ulige), så skal der sendes .0 efter der er divideret med 2
	if(temp & 0b00000001)
		sendString(".5");
	else
		sendString(".0");
	
}
