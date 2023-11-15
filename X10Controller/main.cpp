/*
 * X10Controller.cpp
 *
 * Created: 11/1/2023 10:37:57 AM
 * Author : esben
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "led.h"
#include "SystemController.h"
#include "Transmitter.h"

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
		systemcontroller.loadTemp();
		
		if(systemcontroller.getTemp() >= systemcontroller.getTempThreshold())
			turnOnLED(7);
		else
			turnOffLED(7);
		
		_delay_ms(1000);
	}
}


