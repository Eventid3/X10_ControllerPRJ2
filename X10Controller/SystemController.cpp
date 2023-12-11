/*
 * SystemController.cpp
 *
 * Created: 11/1/2023 12:15:30 PM
 *  Author: esben
 */ 

#include "SystemController.h"

void SystemController::readString(uint8_t maxLength)
{
	/* 
	Læser en modtaget string via UART til bufferen 
	*/
	clearBuffer();
	
	while (!charReady()){}
	
	uint8_t i = 0;

	while (i < maxLength - 1)
	{
		char receivedChar = readChar();

		if (receivedChar == '\n' || receivedChar == '\r')
		{
			break;  // Går ud af loopet hvis der er modtaget newline eller return char
		}
		m_Buffer[i] = receivedChar;
		i++;
	}
	
	m_Buffer[i] = '\0'; // Afslutter med null-termination char
	
}

void SystemController::clearBuffer()
{
	/*
	Denne funktion clearer bufferen til ene af nulls
	*/
	 for (uint8_t i = 0; i < 10; i++)
	 {
		 m_Buffer[i] = '\0';
	 }
}

float SystemController::convertBufferToFloat()
{
	/*
	Konverterer dataen i bufferen til en float
	*/
	return atof(m_Buffer);
}

void SystemController::loadTemp()
{
	/*
	Læser temperaturen fra LM75 sensoren til m_Temperature
	*/
	m_Temperature = LM75_temperature(0) / 2.0f;
}

void SystemController::sendTemp()
{
	/*
	Sender den nuværende temperatur til UserInterfacet
	*/
	loadFloatToBuffer(m_Temperature);
	
	sendString(m_Buffer);
}

void SystemController::sendTempThreshold()
{
	/*
	Sender den nuværende terskelværdi på temperaturen til UserInterfacet
	*/
	loadFloatToBuffer(m_TempThreshold);
	
	sendString(m_Buffer);
}

void SystemController::sendError()
{
	/*
	Sender en fejlbesked
	*/
	sendString("LOCKED!!!!");
}

void SystemController::loadFloatToBuffer(float f)
{
	/*
	Læser en float in i bufferen som en string/const char*
	*/
	clearBuffer();
	
	int intPart = (int)f;
	int decimalPart = (int)((f - intPart) * 10);
	
	snprintf(m_Buffer,sizeof(m_Buffer),"%d.%d",intPart,decimalPart);
}

bool SystemController::codeLockCorrect()
{
	/*
	Tjekker om der er logisk HIGH på den pin 
	der tjekker om kodelåsen er låst op.
	*/
	if (PINA & (1 << PINA0) == 1)
		return true;
	return false;
}

void SystemController::handleInput(char c) 
{
	/*
	Håndterer den modtagne kommando fra UserInterfacet.
	Tjekker desuden om kodelåsen er indstillet korrekt, og 
	sender en fejlmeddelelse hvis dette er tilfældet.
	*/
	
	if(codeLockCorrect())
	{
		switch (c)
		{
			case '1':
				loadTemp();
				//toggleLED(0); // Til debugging
				sendTemp();
				break;
			case '2':
				//toggleLED(1); // Til debugging
				readString(10);
				m_TempThreshold = convertBufferToFloat();
				sendTempThreshold();
				break;
			case '3':
				//toggleLED(2); // Til debugging
				sendTempThreshold();
				break;
			default:
				break;
		}
	}
	else
	{
		sendError();
	}
}