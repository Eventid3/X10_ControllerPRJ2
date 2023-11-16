/*
 * SystemController.cpp
 *
 * Created: 11/1/2023 12:15:30 PM
 *  Author: esben
 */ 

#include "SystemController.h"

void SystemController::readString(unsigned char maxLength)
{
	clearBuffer();
	
	while (!charReady()){}
		
	unsigned int i = 0;

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
	 for (unsigned int i = 0; i < 10; i++)
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

void SystemController::loadFloatToBuffer(float f)
{
	clearBuffer();
	
	int intPart = (int)f;
	int decimalPart = (int)((f - intPart) * 10);
	
	snprintf(m_Buffer,sizeof(m_Buffer),"%d.%d",intPart,decimalPart);
}

void SystemController::handleInput(char c) 
{
	switch (c)
	{
		case '1':
			toggleLED(1);
			break;
		case '2':
			loadTemp();
			toggleLED(0);
			sendTemp();
			break;
		case '3':
			toggleLED(2);
			readString(10);
			m_TempThreshold = convertBufferToFloat();
			break;
		case '4':
			toggleLED(3);
			sendTempThreshold();
			break;
		default:
			break;
	}
	
	//if (m_Buffer != '\0')
	//{
		//if (m_Buffer[0] == 'a' || m_Buffer[0] == 'A') { toggleLED(1); }
		//if (m_Buffer[0] == 'l' || m_Buffer[0] == 'L') 
		//{
			//loadTemp();
			//toggleLED(0);
			//sendTemp();
		//}
	//}
}