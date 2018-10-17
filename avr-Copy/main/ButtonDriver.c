/*
 * buttonDriver.c
 *
 *  Created: 21/03/2018 9:46:38
 *  Author: Kris
 */ 

#include <../headers/buttonDriver.h>
#include <../headers/ledDriver.h>
/**
	Buttons init
    @param *lp function pointer.
	@return void
*/
void buttonsInit(void *lp) {

	funcX = lp;
	//set ports as inports
	PORTE	= PORTE | (1 << PORT7) | (1 << PORT6) | (1 << PORT5) 
	| (1 << PORT4)  ;
	DDRE	=   ~(~DDRE | (1 << PORT7) | (1 << PORT6)
	| (1 << PORT5) | (1 << PORT4));
	
	PORTD	= PORTD | (1 << PORT1);
	DDRD    = ~(~DDRD | 1 << PORT1)  ;
	
	//acrivate interrupt 1 on rising edge
	EICRA	= EICRA | (1<< ISC11) | (1 << ISC10);
	// activate interrupt 7,6,5,4 on rising edge
	EICRB	= EICRA | (1<< ISC71) | (1 << ISC70) | (1<< ISC61) | (1 << ISC60) 
	| (1<< ISC51) | (1 << ISC50) | (1<< ISC41) | (1 << ISC40);
	//enbale the interrupts
	EIMSK	= EIMSK | (1 << INT7) | (1 << INT6) | (1 << INT5) | (1 << INT5)  
	| (1 << INT4)  |(1 << INT1);
}

/**
	ISR button in real time
    @param real-time ISR-> buttonISR.
	@return void
*/
ISR(boutonISR1) {
	funcX(CENTER);
	CallTerminateISR2();
}


ISR(boutonISR4) {
	funcX(NORTH);
	CallTerminateISR2();
}

ISR(boutonISR5) {
	funcX(EAST);
	CallTerminateISR2();
}

ISR(boutonISR6) {
	//printf("hello");
	funcX(WEST);
	CallTerminateISR2();
}

ISR(boutonISR7) {
	funcX(SOUTH);
	CallTerminateISR2();
}