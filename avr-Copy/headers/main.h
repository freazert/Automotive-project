/*
 * main.h
 *
 * Created: 20/06/2018 18:43:35
 *  Author: Kris
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <avr/io.h>

#include "headers/types.h"
//#include "headers/var_pub.h"
#include "headers/defineHeader.h"
#include "headers/canDriver.h"
#include "headers/LedDriver.h"

#ifdef CC
	#include "headers/Subsystem0.h"                /* Model's header file */
	#include "headers/rtwtypes.h"
	#include "headers/zero_crossing_types.h"
#endif // CC
#ifdef WHEEL
	#include "headers/acdDriver.h"
	#include "headers/PWMDriver.h"
#endif // WHEEL
#ifdef DASHBOARD
	#include "headers/ButtonDriver.h"
#endif // DASHBOARD

//remove trampoline def of ISR..
#undef ISR
#include <avr/interrupt.h>
//and add GCC def of ISR :-/
//
int main(void);

void functionLedSet(t_BUTTON);
void functionPWMSet(char);

#include "tpl_os.h"
#include "tpl_app_config.h"



#endif /* MAIN_H_ */