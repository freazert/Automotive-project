/*
 * ButtonDriver.h
 *
 * Created: 21/03/2018 9:45:00
 *  Author: Kris
 */ 


#ifndef BUTTONDRIVER_H_
#define BUTTONDRIVER_H_

#include <tpl_os.h>
#include <tpl_app_config.h>
#include <headers/types.h>

void(*funcX)(t_BUTTON); 
void buttonsInit(void *lp);




#endif /* BUTTONDRIVER_H_ */