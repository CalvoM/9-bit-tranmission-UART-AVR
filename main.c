/*
 * MegaAssembly.c
 *
 * Created: 8/22/2019 12:03:17 PM
 * Author : Calvin Mwadime (CalvoM)
 */ 

#include <avr/io.h>
#include "USART.h"
unsigned int receivedByte;
unsigned int sniffByte;
char hello[] = "MDB INIT";
int main(void)
{   
	//initializing the UART
	usart_init(9600);
	//Welcome message
	DEBUG_PRINTLN("MDB INITIALIZATION");
	//continuously get characters and display
	while(1){
	receivedByte = usart_receive();
	usart_transmit(receivedByte);
	wait(800);	
	}
	
}
