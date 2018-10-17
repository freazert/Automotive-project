/*
 * acdDriver.c
 *
 * Created: 25/04/2018 8:58:09
 *  Author: Kris
 */ 
#include <../headers/acdDriver.h>

/**
    init ADC.

    @param *lp function pointer.
    @return void.
*/
void adcInit(void *lp) {
	
	//enabeling ADC & enabeling trigger
	ADCSRA = ADCSRA | (1 << ADEN) | ADCSRA /*| (1 << ADATE)*/ | (1 << ADIE);
	
	//Enabeling analog input for ADC 3 & set voltage reference
	ADMUX = ADMUX | (1 << MUX1) | ADMUX | (1 << MUX0) | ADMUX 
	| (1 << REFS0) | ADMUX | (1 << REFS1);
	//ADCSRA = ADCSRA | 1 << ADSC;
	
	funcADC = lp;
}

/**
	Conversion starts
    @param void.
    @return void
*/
void ADCstartConversion(void)
{
	//Start single conversion
	ADCSRA = ADCSRA | 1 << ADSC;
}

/**
	Interrupt Service Routine real-time
    @param adc_vect interruption stack.
*/
ISR(adcISR1)
{
	//turn interrupt flag off
	ADCSRA |= (1<<ADIF);
	//Getting ADC data 2 bitshift right
	funcADC(ADCW>>2);
	//end ISR
	CallTerminateISR2();
}