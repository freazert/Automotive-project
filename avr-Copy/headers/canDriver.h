/*
 * canDriver.h
 *
 * Created: 16/05/2018 14:56:07
 *  Author: Kris
 */ 


#ifndef CANDRIVER_H_
#define CANDRIVER_H_

#include <avr/io.h>
//#include <avr/iocan128.h>
//VERY IMPORTANT
#include <avr/interrupt.h>
//#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <headers/types.h>
//#include <headers/var_pub.h>
#include <headers/defineHeader.h>
  

void (*functionCANSpeed)(char value) ;
void (*functionCANButton)(char value);
void (*functionCANForce)(uint16_t force);
void (*functionCANSetSpeed)(char speed);
void (*functionCANCCOn) (char CANOn);

void canInit(void* FunctionCANSpeed, void* FunctionCANButton, void* FunctionCANForce, void* FunctionCANSetSpeed, void* FunctionCANCCOn);
void canSetBaud(void);
void canInitMob(void);
void canInitSend(void);
void canInitRecieve(void);
void canSend(char, uint16_t);
void canStop(void);
void canStart(void);

#endif /* CANDRIVER_H_ */