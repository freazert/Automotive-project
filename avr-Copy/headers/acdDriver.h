/*
 * acdDriver.h
 *
 * Created: 25/04/2018 8:58:22
 *  Author: Kris
 */ 


#ifndef ACDDRIVER_H_
#define ACDDRIVER_H_
 #include <avr/io.h>
#include "headers/rs232.h"
 
 
 
 #include "tpl_os.h"
 #include "tpl_app_config.h"


void(*funcADC)(int c) ; 

void adcInit(void *lp) ;

void ADCstartConversion(void);

#endif /* ACDDRIVER_H_ */