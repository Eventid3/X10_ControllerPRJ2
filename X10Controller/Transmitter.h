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

// This should be in main:
/* const int zeroCrossPin = 21;

void loop() {
	if (Encoder.isSafeToSend) {
		Send Manchester-encoded information to the receiver

		Reset the flag after sending the information:
		Encoder.isSafeToSend = false;
	}
}*/


ISR(INT0_vect);

class Transmitter {
	public:
	Transmitter(int zeroCrossPin); // Constructor
	void Setup();
	//void SendCode(int bit);
	static void ZeroCrossInterrupt();

	private:
	int zeroCrossPin; // In this case zeroCrossPin = pin 21 
	volatile bool isSafeToSend; // flag that indicates ISR triggering (by the zero crossed detector)
	static Transmitter* instance; // Singleton pattern
	// The Singleton pattern ensures that a class has only one instance and provides a global point of access to that instance
};

