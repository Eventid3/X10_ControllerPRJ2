/*
 * Transmitter.cpp
 *
 * Created: 15-11-2023 14:05:07
 *  Author: linev
 */ 

#include "Transmitter.h"


//Transmitter* Transmitter::instance = NULL;

Transmitter::Transmitter(int zeroCrossPin) : zeroCrossPin(zeroCrossPin) {}


void Transmitter::Setup()
 {
	// Configure PD0 (pin 21) as input
	DDRD = 0; // Clear the bit in the DDRD register to set it as an input
	// PD0 corresponds to pin 21 on the ATmega2560

	// Enable external interrupt on INT0 (PD0)
	EICRA |= (1 << ISC01); // Set INT0 to trigger on falling edge
	//EICRA &= ~(1 << ISC00);

	//EIFR |= (1 << INTF0); // Clear any pending interrupt

	sei(); // Enable global interrupts
}

void Transmitter::ZeroCrossInterrupt()
{
	// This function will be called on the falling edge of INT0
	// It indicates a zero crossing event	
	//if (isSafeToSend)
	{
		if(sendCode[codeIndex])
		 {
			 GenerateBurst();
		 }
		 turnOnLED(codeIndex);
		 sendString("codeIndex: ");
		 sendInt(codeIndex);
		 sendChar('\r');
		 sendChar('\n');
		 sendString("value: ");
		 sendInt(sendCode[codeIndex]);
		 sendChar('\r');
		 sendChar('\n');
		 codeIndex++;
		 if (codeIndex==5)
		 {
			 //instance->isSafeToSend = false;
			 EIMSK = 0; // Disable external interrupt INT0
			 writeAllLEDs(0);
		 }
	}
}

void Transmitter::GenerateBurst() const
{
	OCR1A = 65;
	// Init af timer 1
	TCCR1A = 0b00010000;
	TCCR1B = 0b00001001;
	
	_delay_ms(200);
	TCCR1B = 0b00001000;
}




void Transmitter::SendCode(int condition)
{
	sendCode[4] = condition;
	//instance->isSafeToSend = true;
	EIMSK |= (1 << INT0); // Enable external interrupt INT0
}




