/*
 * X10Controller.cpp
 *
 * Created: 11/1/2023 10:37:57 AM
 * Author : esben
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "led.h"
#include "SystemController.h"

SystemController systemcontroller(9600);

ISR(USART0_RX_vect)
{
	char c = readChar();
	
	systemcontroller.handleInput(c);
}

int main()
{
	sei();
	
	initLEDport();
	
	while (1)
	{

	}
}


