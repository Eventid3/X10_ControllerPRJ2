/*
 * uart.c
 *
 * Created: 4/25/2023 8:32:03 AM
 *  Author: esben
 */ 

#include "uart.h"

#define XTAL 16000000

void initUART(unsigned long baudrate, unsigned char databit, unsigned char rx_int)
{
	if (baudrate <= 115200 && baudrate >= 300 && databit <= 8 && databit >= 5)
	{
			// turn on transmit and recieve
			UCSR0B = (1 << RXEN0) | (1 << TXEN0);
			// asynkron mode, no parity, 1 bit stop
			UCSR0C = (databit -5) << 1;
			//baud rate
			UBRR0 = XTAL / (16*baudrate) - 1;
	}
	
	if (rx_int != 0)
	{
		UCSR0B |= (1 << RXCIE0);
	}
}

//returnerer true hvis et tegn er modtaget
unsigned char charReady()
{
	if (((1 << RXC0) & UCSR0A ) != 0)
		return 1;
	else
		return 0;
}

// læser et char fra UDR registeret når den er klar
char readChar()
{
	while (!charReady()) {}
	return UDR0;	
}

// sender et char til UDR når den er klar
void sendChar(char c)
{
	while(((1 << UDRE0) & UCSR0A) == 0) {}
	UDR0 = c;
}

void sendString(char* str)
{
	// mens det pointeren peger på ikke er 0, send det der er der hvor pointeren peger på.
	while (*str != 0)
	{
		sendChar(*str);
		str++;
	}
}

void sendInt(int n)
{
	// array til int string
	char arr[10] = {0,0,0,0,0,0,0,0,0,0};
	
	// konverter fra int til string, og gem i arrayet
	//itoa(n,arr,10);
	snprintf(arr,sizeof(arr),"%i",n);
	
	// send arrayet som string
	sendString(arr);
}