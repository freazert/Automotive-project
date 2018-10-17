#ifndef rs232
#define rs232

#include <stdio.h>
//#include <util/delay.h>
#include <avr/io.h>


void USART0_Transmit (unsigned char data);
void USART0_Transmit_String(char* string);
void init_USART0();
void USART1_Transmit (unsigned char data);
void USART1_Transmit_String(char* string);
void init_USART1();
uint8_t uart_getchar(void);								//used by printf()
int uart_putchar(char c, FILE *stream);			//used by scanf()


#endif
