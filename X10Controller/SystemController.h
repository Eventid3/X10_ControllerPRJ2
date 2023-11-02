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

class SystemController
{
public:
	SystemController() 
	{
		m_Temperature = 123;
	}
	
	void getTemp() const;
private:
	int m_Temperature;
};