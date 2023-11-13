/*
 * SystemController.cpp
 *
 * Created: 11/1/2023 12:15:30 PM
 *  Author: esben
 */ 

#include "SystemController.h"

//void SystemController::toggleLED(unsigned char led_nr)
//{
	//toggleLED(led_nr);
//}

float SystemController::getTemp() const
{
	return m_Temperature;
}

void SystemController::loadTemp()
{
	m_Temperature = LM75_temperature(0);
}

void SystemController::sendTemp() const
{
	sendInt(m_Temperature/2);

	// hvis den sidste bit i tallet er 1 (dvs tallet er ulige), så skal der sendes .0 efter der er divideret med 2
	if(m_Temperature & 0b00000001)
		sendString(".5");
	else
		sendString(".0");
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