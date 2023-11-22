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

const int zeroCrossPin = 21;

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
		OCR1A = 65;
		
		// Init af timer 1
		TCCR1A = 0b00010000;
		TCCR1B = 0b00001001;
		
		systemcontroller.loadTemp();
		
		if(systemcontroller.getTemp() >= systemcontroller.getTempThreshold())
			turnOnLED(7);
		else
			turnOffLED(7);
			//sendCode(false);
		
		_delay_ms(1000);
	}
}


