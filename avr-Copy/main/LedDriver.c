/*
 * LedDriver.c
 *
 * Created: 21/03/2018 9:00:51
 *  Author: Kris
 */ 
#include "../headers/LedDriver.h"

/**
	LEDS init
    @param void.
	@return void
*/
void ledsInit(void)
{
	// All output
	DDRA =  0b11111111;
	
}

/**
	LEDS on
    @param bitmask char.
	@return void
*/
void ledsOn(char bitmask)
{
	PORTA = PORTA | bitmask;	
}
/**
	Turn off LEDS
    @param bitmask char.
	@return void
*/
void ledsOff(char bitmask)
{
	PORTA = ~bitmask & PORTA;
}

/**
	LEDS Toggle -> choose leds to toggle
    @param bitmask char.
	@return void
*/
void ledsToggle(char bitmask)
{	
	PORTA = bitmask ^ PORTA;
}

/**
	LEDS set 
    @param bitmask char -> absolute value.
	@return void
*/
void ledsSet(char bitmask)
{
	PORTA = bitmask;
}