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

void SystemController::loadTemp()
{
	m_Temperature = LM75_temperature(0) / 2.0f;
}

void SystemController::sendTemp() const
{
	char buffer[10];
	int intPart = (int)m_Temperature;
	int decimalPart = (int)((m_Temperature - intPart) * 10);
	
	snprintf(buffer,sizeof(buffer),"%d.%d",intPart,decimalPart);

	sendString(buffer);
}

void SystemController::handleInput(char c) 
{
	switch (c)
	{
		case 'a':
		case 'A':
			toggleLED(1);
			break;
		case 'l':
		case 'L':
			loadTemp();
			toggleLED(0);
			sendTemp();
			break;
		case 'n':
		case 'N':
			toggleLED(2);
			readString(10);
			break;
		case 'r':
		case 'R':
			toggleLED(3);
			sendString(m_Buffer);
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