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

//SystemController systemcontroller(9600);

//ISR(USART0_RX_vect)
//{
	//char c = readChar();
	//
	//systemcontroller.handleInput(c);
//}

Transmitter transmitter(zeroCrossPin);

ISR(INT0_vect)
{
	transmitter.ZeroCrossInterrupt();
}

int main()
{
	sei();
	
	//initUART(9600,1,0);
	initLEDport();
	initSwitchPort();
	initUART(9600,1,0);
	
	sendString("UART init\n\r");
	transmitter.Setup();
	
	while (1)
	{		
		//transmitter.GenerateBurst();
		if (switchOn(1))
		{
			sendString("Startet\r\n");
			transmitter.SendCode(1);
		}
		else if (switchOn(2))
		{
			transmitter.SendCode(0);
		}
		
		//systemcontroller.loadTemp();
		//
		//if(systemcontroller.getTemp() >= systemcontroller.getTempThreshold())
			//turnOnLED(7);
		//else
			//turnOffLED(7);
			////sendCode(false);
		//
		//_delay_ms(1000);
	}
}


