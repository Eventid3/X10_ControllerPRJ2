/*
 * Transmitter.cpp
 *
 * Created: 15-11-2023 14:05:07
 *  Author: linev
 */ 

#include "Transmitter.h"


void Transmitter::Setup()
 {
	// port E til inputs
	DDRE = 0; 
	
	DDRH = 0xFF; //Port H til timer 4 output

	// Disable external interrupt lige for nu
	EIMSK = 0;
	EICRA = 0b00000000; 
	EICRB = 0b00000001; // Set INT4 to trigger on any edge

	m_CodeIndex = 0;
	
	m_SendCode[0] = 1;
	m_SendCode[1] = 1;
	m_SendCode[2] = 1;
	m_SendCode[3] = 0;
	m_SendCode[4] = 1;
}

void Transmitter::ZeroCrossInterrupt()
{
	// This function will be called on the falling edge of INT4
	// It indicates a zero crossing event	
	if(m_SendCode[m_CodeIndex])
	{
		 GenerateBurst();
	}
	 toggleLED(m_CodeIndex);

	m_CodeIndex++;
	if (m_CodeIndex >= 5)
	{
		if (m_SendCode[4])
			turnOnLED(7);
		else
			turnOffLED(7);
			
		EIMSK = 0; // Disable external interrupt INT4
		m_CodeIndex = 0;
	}
}


void Transmitter::GenerateBurst() const
{
	OCR4A = 65;
	// Init af timer 4
	TCCR4A = 0b00010000;
	TCCR4B = 0b00001001;
	
	_delay_ms(300); // 1ms standard i x10 protokollen
	TCCR4B = 0b00001000;
	
	PORTH &= 0b11101111;
}



void Transmitter::SendCode(uint8_t condition)
{
	m_SendCode[4] = condition;
	EIMSK = 0b00010000; // Enable external interrupt INT4
}




