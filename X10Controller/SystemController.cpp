/*
 * SystemController.cpp
 *
 * Created: 11/1/2023 12:15:30 PM
 *  Author: esben
 */ 

#include "SystemController.h"

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
	}
}