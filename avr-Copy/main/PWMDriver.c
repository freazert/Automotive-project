/*
 * PWMDriver.c
 *
 *  Created: 25/04/2018 11:44:33
 *  Author: Kris
 */ 

#include "headers/PWMDriver.h"

/**
	init PWM
    @param void.
	@return void
*/
void pwmInit(void)
{
	
	//OCR0A = 0x70;
   //
   
   //COM0A --> SET OC0A for comparing, WGM -> fast PWM, CS -> ci/O = prescaler/256
	TCCR0A |= (1 << FOC0A) | (1<<COM0A1) | (1 <<COM0A0)| (1<<WGM00)| (1<<WGM01) | (1 << CS02);

	//external output for the OCR0A -> PWM
	DDRB  |= (1 << DDB7);
}

/**
	Set pulse width modulation 
    @param pwmLength char -> 8bits.
	@return void
*/
void pwmSet(char pwmLength)
{
	//Ouput compare regist will compare with timer to generate PWM
	OCR0A = pwmLength; 
}