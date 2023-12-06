/*
 * SystemController.cpp
 *
 * Created: 11/1/2023 12:15:30 PM
 *  Author: esben
 */ 

#include "SystemController.h"

void SystemController::readString(uint8_t maxLength)
{
	clearBuffer();
	
	while (!charReady()){}
	
	uint8_t i = 0;

	while (i < maxLength - 1)
	{
		char receivedChar = readChar();

		if (receivedChar == '\n' || receivedChar == '\r')
		{
			break;  // Exit the loop when newline character is received
		}
		m_Buffer[i] = receivedChar;
		i++;
	}
	
	m_Buffer[i] = '\0';
	
	//sendString(m_Buffer);
}

void SystemController::clearBuffer()
{
	 for (uint8_t i = 0; i < 10; i++)
	 {
		 m_Buffer[i] = '\0';
	 }
}

float SystemController::convertBufferToFloat()
{
	return atof(m_Buffer);
}

void SystemController::loadTemp()
{
	m_Temperature = LM75_temperature(0) / 2.0f;
}

void SystemController::sendTemp()
{
	loadFloatToBuffer(m_Temperature);
	
	sendString(m_Buffer);
}

void SystemController::sendTempThreshold()
{
	loadFloatToBuffer(m_TempThreshold);
	
	sendString(m_Buffer);
}

void SystemController::sendError()
{
	sendString("LOCKED!!!!");
}

void SystemController::loadFloatToBuffer(float f)
{
	clearBuffer();
	
	int intPart = (int)f;
	int decimalPart = (int)((f - intPart) * 10);
	
	snprintf(m_Buffer,sizeof(m_Buffer),"%d.%d",intPart,decimalPart);
}

bool SystemController::codeLockCorrect()
{
	//TODO
	if (PINA & (1 << PINA0) == 1)
		return true;
	return false;
}

void SystemController::handleInput(char c) 
{
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
				//toggleLED(1); // til debugging
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