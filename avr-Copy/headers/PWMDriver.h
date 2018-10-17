/*
 * PWMDriver.h
 *
 * Created: 25/04/2018 11:44:57
 *  Author: Kris
 */ 


#ifndef PWMDRIVER_H_
#define PWMDRIVER_H_


#include <tpl_os.h>
#include <tpl_app_config.h>


#include <avr/io.h>

void pwmInit(void);

void pwmSet(char);


#endif /* PWMDRIVER_H_ */