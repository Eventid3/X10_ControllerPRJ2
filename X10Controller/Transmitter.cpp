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
	
	DDRA = 0xFF;
	PORTA |= (1 << 0);
	PORTH |= (1<<PINH4);

	// Disable external interrupt lige for nu
	EIMSK = 0;
	EICRA = 0b00000000; 
	EICRB = 0b00000011; // Set INT4 to trigger on rising edge
	
	EIMSK = 0b00010000; // tænd zerocross

	m_CodeIndex = 0;
	
	m_ZeroCrossFlag = false;
	
	m_SendCode[0] = 1;
	m_SendCode[1] = 0;
	m_SendCode[2] = 1;
	m_SendCode[3] = 0;
	m_SendCode[4] = 1;
	m_SendCode[5] = 0;
	m_SendCode[6] = 0;
	m_SendCode[7] = 0;
	m_SendCode[8] = 0;
	m_SendCode[9] = 0;
}

void Transmitter::ZeroCrossInterrupt()
{
	// This function will be called on the falling edge of INT4
	// It indicates a zero crossing event	
	if(m_SendCode[m_CodeIndex])
	{
		 GenerateBurst();
	}
	toggleLED((m_CodeIndex/2) % 5);
	m_CodeIndex++;
	m_ZeroCrossFlag = true;
	
	if (m_CodeIndex >= 10)
	{
		if (m_SendCode[8])
			turnOnLED(7);
		else
			turnOffLED(7);
			
		//EIMSK = 0; // Disable external interrupt INT4
		m_ZeroCrossFlag = false; // Disable zerocross interrupt flag
		m_CodeIndex = 0;
			
	}
}


void Transmitter::GenerateBurst() const
{
	DDRH = 0xFF; //Port H til timer 4 output
	OCR4A = 65;
	// Init af timer 4
	TCCR4A = 0b00010000;
	TCCR4B = 0b00001001;
	TDelay(1); // 1ms standard i x10 protokollen
	TCCR4B = 0b00001000;
	
	//PORTH &= (1<<PINH4);
	DDRH = 0;
}

void Transmitter::SetZeroCrossFlag()
{
	m_ZeroCrossFlag = true;
}

void Transmitter::DisableZeroCrossFlag()
{
	m_ZeroCrossFlag = false;
}


void Transmitter::SendCode(uint8_t command)
{
	if (command)
	{
		m_SendCode[8] = 1;
		m_SendCode[9] = 0;
	}
	else
	{
		m_SendCode[8] = 0;
		m_SendCode[9] = 0;		
	}
	//EIMSK = 0b00010000; // Enable external interrupt INT4
}

void Transmitter::TDelay(float ms) const
{
	ms = ms > 32.0f ? 32.0f : ms;
	ms /= 1000.0f;
	TCNT5 = (int)(65536.0f - ms*16000000.0f/8.0f); // load rigtigt tal i timeren
	
	// init timer med 8 prescaler og start den
	TCCR5A = 0b00000000;
	TCCR5B = 0b00000010;
	
	while ((TIFR5 & (1<<0)) == 0) { /* bliv her indtil timeren er nul */ }
	
	TCCR5B = 0; // stop counteren
	TIFR5 = 1; // nulstil overflow flag
}



