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
#include "SystemController.h"

uint8_t Transmitter::m_CodeIndex;
uint8_t Transmitter::m_SendCode[10];
bool Transmitter::m_ZeroCrossFlag;
SystemController systemcontroller(9600);

ISR(INT4_vect);
ISR(USART0_RX_vect);

int main()
{
	bool tempHandle = false;
	float hysterese = 0.5f;
	sei();
	
	
	while (1)
	{		
		systemcontroller.loadTemp();
		
		if(systemcontroller.getTemp() >= systemcontroller.getTempThreshold() + hysterese && !tempHandle)
		{
			tempHandle = true;
			systemcontroller.GetTransmitter().SendCode(1);
			systemcontroller.GetTransmitter().SetZeroCrossFlag();
			turnOnLED(5);
		}
		
		else if (systemcontroller.getTemp() <= systemcontroller.getTempThreshold() - hysterese && tempHandle)
		{
			tempHandle = false;
			systemcontroller.GetTransmitter().SendCode(0);
			systemcontroller.GetTransmitter().SetZeroCrossFlag();
			turnOffLED(5);	
		}
		
		_delay_ms(1000);
		
		
		// --- TEST CODE ----
		// ------------------
		//tempHandle = true;
		//systemcontroller.GetTransmitter().SendCode(1);
		//systemcontroller.GetTransmitter().SetZeroCrossFlag();
		//turnOnLED(5);
		//_delay_ms(1500);
		//tempHandle = false;
		//systemcontroller.GetTransmitter().SendCode(0);
		//systemcontroller.GetTransmitter().SetZeroCrossFlag();
		//turnOffLED(5);
		//_delay_ms(1500);
		
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


