/*
 * SystemController.cpp
 *
 * Created: 11/1/2023 10:59:13 AM
 *  Author: esben
 */ 
#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "uart.h"
#include "led.h"
#include "switch.h"
#include "lm751.h"

class SystemController
{
public:
	SystemController(int baud, int databit = 8, int rx_int = 1) 
	{
		LM75_init();
		//initLEDport();
		initSwitchPort();
		
		initUART(baud, databit, rx_int); // Initialize UART: Baud = 9600, 8 data bits
		
		m_Temperature = LM75_temperature(0) / 2.0f;
		m_TempThreshold = 24.0f; 
		m_Humidity = 0;
		m_CO2 = 0;
	}
	
	//void toggleLED(unsigned char led_nr);
	
	void handleInput(char c);
	
	void loadTemp();
	float getTemp() const { return m_Temperature; }
	float getTempThreshold() const { return m_TempThreshold; }
	void sendTemp() const;
private:
	float m_Temperature; 
	float m_TempThreshold;
	float m_Humidity;
	float m_CO2;
};