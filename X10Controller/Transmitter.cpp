/*
 * Transmitter.cpp
 *
 * Created: 15-11-2023 14:05:07
 *  Author: linev
 */ 

#include "Transmitter.h"


void Transmitter::setup()
 {
	 /*
	 Denne funktion instiller alle de nødvændige porte Transmitteren skal bruge.
	 Initierer desuden startkoden til de rigtige værdier.
	 */
	 
	DDRE = 0; // Port E til inputs til zero cross detection.
	
	// Pin4 på Port H til burst output. Tændes først i GenerateBurst funktionen.
	PORTH |= (1<<PINH4); 

	// Disable external interrupt lige for nu
	EIMSK = 0;
	EICRA = 0b00000000; 
	EICRB = 0b00000011; // INT4/ZeroCross trigger på rising edge
	
	EIMSK = 0b00010000; // Tænd for INT4

	m_CodeIndex = 0;
	
	m_ZeroCrossFlag = false;
	
	m_SendCode[0] = 1;
	m_SendCode[1] = 0;
	m_SendCode[2] = 1;
	m_SendCode[3] = 0;
	m_SendCode[4] = 1;
	m_SendCode[5] = 0;
	m_SendCode[6] = 0;
	m_SendCode[7] = 1;
	m_SendCode[8] = 0;
	m_SendCode[9] = 0;
}

void Transmitter::zeroCrossInterrupt()
{
	/*
	Denne funktion bliver kaldt på et ZeroCross interrupt på INT4.
	*/

	if(m_SendCode[m_CodeIndex])
	{
		 generateBurst();
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
			
		m_ZeroCrossFlag = false; // Disable zerocross interrupt flag
		m_CodeIndex = 0;
	}
}


void Transmitter::generateBurst() const
{
	/*
	Genererer et squarewave signal på 120kHz på Port H Pin4.
	*/
	
	DDRH = 0xFF; //Port H til timer 4 output
	OCR4A = 65;
	// Init af timer 4
	TCCR4A = 0b00010000;
	TCCR4B = 0b00001001;
	timerDelay(1); // 1ms standard i x10 protokollen
	TCCR4B = 0b00001000;
	
	DDRH = 0; // Sluk for port H
}

void Transmitter::setZeroCrossFlag()
{
	m_ZeroCrossFlag = true;
}

void Transmitter::disableZeroCrossFlag()
{
	m_ZeroCrossFlag = false;
}


void Transmitter::sendCode(uint8_t command)
{
	/*
	Indstiller de sidste to bit m_SendCode til de rigtige værdier, afhængigt af input.
	*/
	if (command)
	{
		// Indstil m_SendCode til at åbne vinduet
		m_SendCode[8] = 1;
		m_SendCode[9] = 0;
	}
	else
	{
		// Indstil m_SendCode til at lukke vinduet
		m_SendCode[8] = 0;
		m_SendCode[9] = 1;		
	}
}

void Transmitter::timerDelay(float ms) const
{
	/*
	Delay funktion der tager et antal millisekunder som input, og 
	genererer et delay af den længde på en Mega2560 timer.
	*/
	
	ms = ms > 32.0f ? 32.0f : ms; // 32ms er maks for timeren
	ms /= 1000.0f;
	TCNT5 = (int)(65536.0f - ms*16000000.0f/8.0f); // load rigtigt tal i timeren
	
	// init timer med 8 prescaler og start den
	TCCR5A = 0b00000000;
	TCCR5B = 0b00000010;
	
	while ((TIFR5 & (1<<0)) == 0) { /* bliv her indtil timeren er nul */ }
	
	TCCR5B = 0; // stop counteren
	TIFR5 = 1; // nulstil overflow flag
}



