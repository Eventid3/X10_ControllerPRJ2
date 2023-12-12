/*
 * uart.h
 *
 * Created: 4/25/2023 8:32:33 AM
 *  Author: esben
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>

void initUART(unsigned long baudRate, unsigned char databit, unsigned char rx_int);
unsigned char charReady();
char readChar();
void sendChar(char c);
void sendString(char* str);
void sendInt(int n);
