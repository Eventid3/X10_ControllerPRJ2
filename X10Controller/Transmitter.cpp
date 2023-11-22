/*
 * Transmitter.cpp
 *
 * Created: 15-11-2023 14:05:07
 *  Author: linev
 */ 

#include "Transmitter.h"


Transmitter* Transmitter::instance = NULL;

Transmitter::Transmitter(int zeroCrossPin) : zeroCrossPin(zeroCrossPin), isSafeToSend(false) {
	instance = this;
}

ISR(INT0_vect) 
{
	Transmitter::ZeroCrossInterrupt();
}

void Transmitter::Setup()
 {
	// Configure PD0 (pin 21) as input
	DDRD &= ~(1 << PD0); // Clear the bit in the DDRD register to set it as an input
	// PD0 corresponds to pin 21 on the ATmega2560

	// Enable external interrupt on INT0 (PD0)
	EICRA |= (1 << ISC01); // Set INT0 to trigger on falling edge
	EICRA &= ~(1 << ISC00);

	EIFR |= (1 << INTF0); // Clear any pending interrupt
	EIMSK |= (1 << INT0); // Enable external interrupt INT0

	sei(); // Enable global interrupts
}

void Transmitter::ZeroCrossInterrupt()
{
	// This function will be called on the falling edge of INT0
	// It indicates a zero crossing event
	instance->isSafeToSend = true;
	
	// Sets the value of the isSafeToSend member variable to true for the instance of the Encoder class
	// that the instance pointer is pointing to.
}



/*
void Transmitter::SendCode(int &condition)const
{	
	
	if (condition==1)
	{
			int array[5]=[1,1,1,0,1]
				for (int i=0;i<5;i++)
				{
					if (Transmitter.isSafeToSend)
					{
						if (array[i]=1)
						{
							// Init af timer 1:
							TCCR1A = 0b00010000; //Sætter CTC mode
							TCCR1B = 0b00001001; //Sætter CTC mode 00001 og prescaler 010
							OCR1A = 65; //Værdi til OCR1A register.
						}
						Transmitter.isSafeToSend = false;
					}
				}
	}

	if (condition==0)
	{
		int array[5]=[1,1,1,0,0]
			for (int i=0;i<5;i++)
			{
				if (Transmitter.isSafeToSend)
				{
					if (array[i]=1)
					{
						// Init af timer 1:
						TCCR1A = 0b00010000; //Sætter CTC mode
						TCCR1B = 0b00001001; //Sætter CTC mode 00001 og prescaler 010
						OCR1A = 65; //Værdi til OCR1A register.
					}
				Transmitter.isSafeToSend = false;
				}
			}
	}
}
*/



