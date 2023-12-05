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

unsigned char Transmitter::m_CodeIndex;
unsigned char Transmitter::m_SendCode[5];
bool Transmitter::m_ZeroCrossFlag;
SystemController systemcontroller(9600);

ISR(INT4_vect);
ISR(USART0_RX_vect);

int main()
{
	bool tempHandle = false;
	sei();
	
	initLEDport();
	initSwitchPort();
	
	while (1)
	{		
		/*systemcontroller.loadTemp();
		
		// TODO Hysterese!
		
		if(systemcontroller.getTemp() >= systemcontroller.getTempThreshold() && !tempHandle)
		{
			tempHandle = true;
			systemcontroller.GetTransmitter().SendCode(1);
			systemcontroller.GetTransmitter().SetZeroCrossFlag();
			turnOnLED(5);
	
		}
		
		else if (systemcontroller.getTemp() <= systemcontroller.getTempThreshold() && tempHandle)
		{
			tempHandle = false;
			systemcontroller.GetTransmitter().SendCode(0);
			systemcontroller.GetTransmitter().SetZeroCrossFlag();
			turnOffLED(5);
			
		}*/
		
		//_delay_ms(1000);
		
		
		// --- TEST CODE ----
		// ------------------
		tempHandle = true;
		systemcontroller.GetTransmitter().SendCode(1);
		systemcontroller.GetTransmitter().SetZeroCrossFlag();
		turnOnLED(5);
		_delay_ms(1500);
		tempHandle = false;
		systemcontroller.GetTransmitter().SendCode(0);
		systemcontroller.GetTransmitter().SetZeroCrossFlag();
		turnOffLED(5);
		_delay_ms(1500);
		
	}
}

ISR(INT4_vect)
{
	toggleLED(6);
		
	if (systemcontroller.GetTransmitter().ReadyToRecieve())
	{
		systemcontroller.GetTransmitter().DisableZeroCrossFlag();
		systemcontroller.GetTransmitter().ZeroCrossInterrupt();
	}
}

ISR(USART0_RX_vect)
{
	char c = readChar();
	
	systemcontroller.handleInput(c);
}


