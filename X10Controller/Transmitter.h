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
	
	void setup();
	void sendCode(uint8_t);
	void generateBurst() const;
	void zeroCrossInterrupt();
	void setZeroCrossFlag();
	void disableZeroCrossFlag();
	bool readyToRecieve() const { return m_ZeroCrossFlag; }
		
	void timerDelay(float ms) const;
	
private:
	static uint8_t m_CodeIndex;
	static uint8_t m_SendCode[10];
	
	static bool m_ZeroCrossFlag;
};

#endif