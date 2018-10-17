/*
 * acdDriver.h
 *
 * Created: 25/04/2018 8:58:22
 *  Author: Kris
 */ 


#ifndef ACDDRIVER_H_
#define ACDDRIVER_H_
 #include "asf.h"

void(*funcADC)(int c) ; 

void adcInit(void *lp) ;


#endif /* ACDDRIVER_H_ */