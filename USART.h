#ifndef USART_H
#define USART_H

#include <avr/io.h>

#ifdef F_CPU
#define F_CPU 16000000UL
#endif
#define CD_INACTIVE				0x00
#define CD_DISABLED				0x01
#define CD_ENABLED				0x02
#define CD_SESSION_IDLE			0x03
#define CD_VEND					0x04

//MDB Commands for Cashless Device
#define CASHLESS_ADDRESS_1		0x110
#define MDB_SETUP				0x111
#define MDB_POLL				0x112
#define MDB_VEND				0x113
#define MDB_READER				0x114
#define MDB_REVALUE				0x115//OPTIONAL
#define MDB_EXPANSION			0x117

#define CASHLESS_ADDRESS_2		0x160
#define MDB_SETUP_2				0x161
#define MDB_POLL_2				0x162
#define MDB_VEND_2				0x163
#define MDB_READER_2			0x164
#define MDB_REVALUE_2			0x165//OPTIONAL
#define MDB_EXPANSION_2			0x167


//SETUP Sub-commands
#define MDB_SETUP_CFG_DATA 0x00
#define MDB_SETUP_PRICES   0x01

//VEND Sub-Commands
#define MDB_VEND_REQUEST 0x00
#define MDB_VEND_CANCEL 0x01
#define MDB_VEND_SUCCESS 0x02
#define MDB_VEND_FAILURE 0x03
#define MDB_VEND_SESSION_COMPLETE 0x04
#define MDB_VEND_CASH_SALE 0x05
// #define MDB_VEND_NEGATIVE_VEND_REQUEST 0x06 //LEVEL 3+

//READER Sub-commands
#define MDB_READER_DISABLE 0x00
#define MDB_READER_ENABLE 0x01
#define MDB_READER_CANCEL 0x02
// #define MDB_READER_DATA_ENTRY_RESPONSE 0x03 //LEVEL 3+

//EXPANSION Sub-Commands
#define MDB_EXPANSION_REQUEST_ID		0x00
#define MDB_EXPANSION_DIAGNOSTICS		0xFF
#define MDB_EXPANSION_ENABLE_OPTIONS	0x04

/* Responses to VMC Commands*/

//Universal Responses
#define MDB_ACK 0x100
#define MDB_RET 0xAA
#define MDB_NAK 0xFF

//POLL Responses
#define CD_JUST_RESET 0x00
#define CD_READER_CONFIG_INFO 0x01
#define CD_DISPLAY_REQUEST 0x02
#define CD_BEGIN_SESSION 0x03
#define CD_SESSION_CANCEL_REQUEST 0x04
#define CD_VEND_APPROVED 0x05
#define CD_VEND_DENIED 0x06
#define CD_END_SESSION 0x07
#define CD_CANCELLED 0x08
#define CD_PERIPHERAL_ID 0x09
#define CD_MALFUNCTION_ERROR 0x0A
#define CD_CMD_OUT_OF_SEQUENCE 0x0B
#define CD_DIAGNOSTIC_RESPONSE 0xFF

//functions
void wait(uint32_t time);
void DEBUF_PRINTLN(char message []);
void DEBUG_PRINT(char message []);
void usart_init(uint16_t baud_rate);
void usart_transmit(unsigned int data);
unsigned int usart_receive();
#endif