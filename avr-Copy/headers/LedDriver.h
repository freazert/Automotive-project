/*
 * LedDriver.h
 *
 * Created: 21/03/2018 8:57:59
 *  Author: Kris
 */ 


#ifndef LEDDRIVER_H_
#define LEDDRIVER_H_


#include <avr/io.h>

#include <tpl_os.h>
#include <tpl_app_config.h>

void ledsInit(void);
void ledsOn(char bitmask);
void ledsOff(char bitmask);
void ledsToggle(char bitmask);
void ledsSet(char bitmask);

#endif /* LEDDRIVER_H_ */