/*
 * Transmitter.h
 *
 * Created: 15-11-2023 14:05:31
 *  Author: linev
 */ 

#ifndef X10TRANSMITTER
#define X10TRANSMITTER

#define F_CPU 16000000
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "led.h"
#include "uart.h"

class Transmitter
{
	public:
	Transmitter(){}
	
	void Setup();
	void SendCode(unsigned char);
	static unsigned char m_CodeIndex;
	static unsigned char m_SendCode[5];
	void GenerateBurst() const;
	
	void ZeroCrossInterrupt();
};

#endif