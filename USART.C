#include "USART.h"
#include <string.h>
#include <util/delay.h>
char cashless_2 [] = "160";
char cashless_1 [] = "110";
char poll_1 [] = "112";
char poll_2 [] = "162";

void DEBUG_PRINT(char message []){
	for(int m=0; m<strlen(message);m++){
		while(!(UCSR0A &(1<<UDRE0)));
		UDR0 = message[m];
	}
}

void wait(uint32_t time){
	for (int f=0;f<time;f++)
	{
		for (int f=0;f<(time*2);f++)
		{
			
		}
	}
}

void DEBUG_PRINTLN(char message []){
	for(int m=0; m<strlen(message);m++){
		while(!(UCSR0A &(1<<UDRE0)));
		UDR0 = message[m];
	}
	while(!(UCSR0A &(1<<UDRE0)));
	UDR0 = '\n';
}

void usart_init(uint16_t baud_rate){
	//setting baud_rate
	uint16_t ubrr = (F_CPU/16/baud_rate)-1;
	UBRR3H = (unsigned char)(ubrr >> 8);
	UBRR3L = (unsigned char) ubrr;
	UBRR2H = (unsigned char)(ubrr >> 8);
	UBRR2L = (unsigned char) ubrr;
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	//enable transmitter and receiver and setting bit to enable 9 bit transmission 
	UCSR3B = (1 << RXEN3) | (1 << TXEN3) | (1 << UCSZ32);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << UCSZ02);
	UCSR0B = (1 << RXEN2) | (1 << TXEN2) | (1 << UCSZ22);
	//set the stop bit to 1 bit before any more work
	UCSR3C &= ~(1 << USBS3); 
	UCSR0C &= ~(1 << USBS0); 
	UCSR2C &= ~(1 << USBS2);
	//set frame format : 9bit no parity	
	UCSR3C =  (1 << UCSZ30) | (1 << UCSZ31);
	UCSR0C =  (1 << UCSZ00) | (1 << UCSZ01);
	UCSR2C =  (1 << UCSZ20) | (1 << UCSZ21);
	//stop any transmission
	UCSR1A = (1 << TXC3);
	UCSR0A = (1 << TXC0);
	UCSR2A = (1 << TXC2);
}
void usart_transmit(unsigned int data){
	//check if the data register is empty
	while(!(UCSR0A & (1 << UDRE0)));
	// display on the screen i.e. Serial
	if(data == CASHLESS_ADDRESS_2){
		for(int k=0;k<strlen(cashless_2);k++){
			while(!(UCSR0A & (1 << UDRE0)));
			UDR0 = cashless_2[k];
		}
		while(!(UCSR0A &(1<<UDRE0)));
		UDR0 = '\n';		
	}
	else if(data = CASHLESS_ADDRESS_1){
		for(int k=0;k<strlen(cashless_1);k++){
			while(!(UCSR0A & (1 << UDRE0)));
			UDR0 = cashless_1[k];
		}
		while(!(UCSR0A &(1<<UDRE0)));
		UDR0 = '\n';
	}
	else if(data = MDB_POLL){
		for(int k=0;k<strlen(poll_1);k++){
			while(!(UCSR0A & (1 << UDRE0)));
			UDR0 = poll_1[k];
		}
		while(!(UCSR0A &(1<<UDRE0)));
		UDR0 = '\n';
	}
	else if(data = MDB_POLL_2){
		for(int k=0;k<strlen(poll_2);k++){
			while(!(UCSR0A & (1 << UDRE0)));
			UDR0 = poll_2[k];
		}
		while(!(UCSR0A &(1<<UDRE0)));
		UDR0 = '\n';
	}
	else{
		UDR0="-";
	_delay_ms(500);
}
}
unsigned int usart_receive(){
	unsigned char error_status,data_msb,data_lsb;
	/*
	error_status - Checks for the errors during reception e.g. Frame Error(FE), Data Overrun Error(DO), Parity Error(PE)
	data_msb - Gets the 9th bit from the RXB8
	data_lsb - Gets the 8bit data from the UDR
	*/
	//Check if the receive_complete flag is set else do nothing
	while(!(UCSR3A & (1<<RXC3)));
	error_status = UCSR3A;
	data_msb = UCSR3B;
	data_lsb = UDR3;
	//check if error was present
	//if(error_status & (1 << FE1) |(1<<DOR1) | (1<<PE1) ) return -1;
	data_msb = (data_msb >> 1) & 0x01;
	return ((data_msb <<8) | data_lsb);
}
unsigned int usart_receive2(){
	unsigned char error_status,data_msb,data_lsb;
	/*
	error_status - Checks for the errors during reception e.g. Frame Error(FE), Data Overrun Error(DO), Parity Error(PE)
	data_msb - Gets the 9th bit from the RXB8
	data_lsb - Gets the 8bit data from the UDR
	*/
	//Check if the receive_complete flag is set else do nothing
	while(!(UCSR2A & (1<<RXC2)));
	error_status = UCSR2A;
	data_msb = UCSR2B;
	data_lsb = UDR2;
	//check if error was present
	//if(error_status & (1 << FE1) |(1<<DOR1) | (1<<PE1) ) return -1;
	data_msb = (data_msb >> 1) & 0x01;
	return ((data_msb <<8) | data_lsb);
}
