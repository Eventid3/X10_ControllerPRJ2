/*
 * Transmitter.h
 *
 * Created: 15-11-2023 14:05:31
 *  Author: linev
 */ 

#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>



ISR(INT0_vect);

class Transmitter
{
	private:
	int zeroCrossPin; // In this case zeroCrossPin = pin 21
	static Transmitter* instance; // Singleton pattern
	
	public:
	Transmitter(int zeroCrossPin); // Constructor
	void Setup();
	void SendCode(int)const;
	volatile bool isSafeToSend; // flag that indicates ISR triggering (by the zero crossed detector)
	
	static void ZeroCrossInterrupt();
};

