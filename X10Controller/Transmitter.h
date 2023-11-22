/*
 * Transmitter.h
 *
 * Created: 15-11-2023 14:05:31
 *  Author: linev
 */ 

#pragma once
#define F_CPU 16000000
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "led.h"
#include "uart.h"



ISR(INT0_vect);

class Transmitter
{
	private:
	int zeroCrossPin; // In this case zeroCrossPin = pin 21
	//static Transmitter* instance; // Singleton pattern
	
	
	public:
	Transmitter(int zeroCrossPin); // Constructor
	
	void Setup();
	void SendCode(int);
	int codeIndex = 0;
	int sendCode[5] = {1,1,1,0,1};
	//bool isSafeToSend; // flag that indicates ISR triggering (by the zero crossed detector)
	void GenerateBurst() const;
	
	void ZeroCrossInterrupt();
};

