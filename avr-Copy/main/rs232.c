#include "../headers/rs232.h"

//#define UART_DEBUG

void USART0_Transmit(unsigned char data) {
	while(!(UCSR0A & (1<<UDRE0))); //wacht tot transmit buffer leeg is
	UDR0 = data;
}

void USART0_Transmit_String(char* string) {
	for(int i = 0; string[i] != '\0'; i++) {
		USART0_Transmit(string[i]);
	}
}

void USART1_Transmit(unsigned char data) {
	while(!(UCSR1A & (1<<UDRE1))); //wacht tot transmit buffer leeg is
	UDR1 = data;
}

void USART1_Transmit_String(char* string) {
	for(int i = 0; string[i] != '\0'; i++) {
		USART1_Transmit(string[i]);
	}
}


void init_USART0() {
		/* initialize USART0 */
	UBRR0H = 0;
	UBRR0L = 51; //baudrate 9600 for 8 Mhz
	UCSR1C = (0<<UMSEL0) | (0<<UPM0) | (0<<USBS0) | (3<<UCSZ0); //1 stop bits, no parity, 8 data bits
	UCSR0B = (1 << RXEN0) | (1 << TXEN0); //Rx & Tx enabled
	#ifdef UART_DEBUG
	USART0_Transmit_String("\n\rUSART0 initialized...\n\r");
	#endif
}

void init_USART1() {
		/* initialize USART1 */
	UBRR1H = 0;
	UBRR1L = 51; //baudrate 9600 for 8 Mhz
	UCSR1C = (0<<UMSEL1) | (0<<UPM1) | (0<<USBS1) | (3<<UCSZ1); //1 stop bits, no parity, 8 data bits
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);
	#ifdef UART_DEBUG
	USART1_Transmit_String("\n\rUSART1 initialized...\n\r");
	#endif
}

int uart_putchar(char c, FILE *stream)
{
    if (c == '\n') uart_putchar('\r', stream);

    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;

    return 0;
}

uint8_t uart_getchar(void)
{
    while( !(UCSR0A & (1<<RXC0)) );
    return(UDR0);
}
