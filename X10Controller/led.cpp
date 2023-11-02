/*************************************************
* "LED.C"                                        *
* Implementation file for "Mega2560 LED driver"  *
* Henning Hargaard, 22/9 2015                    *
**************************************************/
#include <avr/io.h>
#define MAX_LED_NR 7

void initLEDport()
{
	// portb til udgang
	DDRB = 0xFF;
	// sluk alle led'er
	PORTB = 0;
}

void writeAllLEDs(unsigned char pattern)
{
  // Hent parameteren og skriv til lysdioderne
  PORTB = pattern;   
}

void turnOnLED(unsigned char led_nr)
{
	// Lokal variabel
	unsigned char mask;
	// Vi skal kun lave noget, hvis led_nr < 8
	if (led_nr <= MAX_LED_NR)
	{
		// Dan maske på basis af parameteren (led_nr)
		mask = 0b00000001 << led_nr;
		// Tænd den aktuelle lysdiode (de andre ændres ikke)
		PORTB = PINB | mask;
	}   
}

void turnOffLED(unsigned char led_nr)
{
	unsigned char mask;
	if (led_nr <= MAX_LED_NR)
	{
		// Dan inverteret maske med et 0 det sted hvor LED'en der skal slukkes er
		mask = ~(0b00000001 << led_nr);
		// Nulstil LED'en med en AND - de andre LED'er ændres ikke
		PORTB = PINB & mask;
	}
}

void toggleLED(unsigned char led_nr)
{
	unsigned char mask;
	if (led_nr <= MAX_LED_NR)
	{
		// Dan maske med et 1'tal der hvor LED'en skal toggles
		mask = 0b00000001 << led_nr;
		// Toggle LED'en med en EOR
		PORTB = PINB ^ mask;
	}
}
