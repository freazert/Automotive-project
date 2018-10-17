/*
 * defineHeader.h
 *
 * Created: 20/06/2018 18:10:34
 *  Author: Kris
 */ 


#ifndef DEFINEHEADER_H_
#define DEFINEHEADER_H_


#define DEBUG


#ifdef DEBUG
#include "headers/rs232.h"
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
#endif // DEBUG

#define WHEEL 
//#undef WHEEL
//#undef CC


#endif /* DEFINEHEADER_H_ */