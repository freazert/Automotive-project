

#include <headers/main.h>

//t_ECU this_ECU = DASHBOARD;

TASK(stopCANTask)
{
	canStop();
	canStart();
	printf("can started again \n");
	TerminateTask();

}

TASK(secondTask)
{
	//PORTA |=2;
	//test stop
	ChainTask(stopCANTask);
	//TerminateTask();
}

TASK(startTask)
{
	ChainTask(secondTask);
}



/*
 * periodic task set up by trampoline OS in the goil file.
 * Changing the duration is both possible in the main function by setting (TCCR2A)
 */
TASK(periodicTask)
{
	#if defined(DASHBOARD)
		//nothing just receiving and displaying and sending buttons.	
	#elif defined(WHEEL)
		printf("send 1 \n");
		// wheel needs ADC interrupt when changing potmeter
		ADCstartConversion();
	#elif defined(CC)
			//symilunk model update
			if(rtU.activate1 || rtU.resume1) {
					canSend(4, 1);
					ledsSet(1);
				} else if (rtU.deactivate1 || rtU.abrogate1) {
					canSend(4,0);
					ledsSet(0);
			}
			/* Step the model */
			Subsystem0_step();
			
			rtU.activate1 = false;
			rtU.deactivate1 = false;
			rtU.abrogate1 = false;
			rtU.resume1 = false;
			
			printf("power: %d N \n", rtY.Power1);
			printf("actual speed: %d kmph \n", rtU.ActualSpeed1);
			
			canSend(3,rtY.Power1);

	#endif // defined(dashboard//wheel//CC)
	
	TerminateTask();
}

// reveive a button from cc back from CAN
void FunctionCANButton(t_BUTTON c){
	#ifdef CC
		switch(c) {
			//North button - activate
			case NORTH:
				printf("activate\n");
				rtU.activate1 = true;
				break;
			//East button - abrogate
			case EAST:
				rtU.abrogate1 = true;
				break;
			//center button
			case CENTER:
			
			break;
			//west button
			case WEST:
				rtU.resume1 = true;
				break;
			//south button
			case SOUTH:
				printf("deactivate\n");
				rtU.deactivate1 = true;
				break;
			default:
				break;
		}
		
#endif
}
//#endif

	//when an ADC interrupt happens we change light and also send it to cruice control
	void ADCinterrupt(int c)
	{
		#if defined(WHEEL) || defined(DASHBOARD)
		printf("the integer is %d", c);
		canSend(1,c);
		ledsSet(c);
	#endif	
	}
	
//#endif // WHEEL
//When CC is eaceiving the speed
void FunctionCANSpeed(char value){
#ifdef CC 
	rtU.ActualSpeed1 = value;
	rtU.DesiredSpeed1 = value;
	//ledsSet(value);
	//#ifdef DEBUG
	printf("ID1 Data: %d \n", value);
	//#endif
#endif
} // CC

// print out the force received via CAN
void FunctionCANForce(uint16_t value){
	#ifdef DEBUG
		printf("ID3 Data: %d \n", value);
	#endif
}

//Print out the set speed via CAN
void FunctionCANSetSpeed(char value){
	#ifdef DEBUG
		printf("ID4 Data: %c \n", value);
	#endif
}

//receive the status of CC
void FunctionCANCCOn(char value){
	#ifdef DEBUG
		printf("ID5 Data: %c \n", value);
	#endif
}

// testing the canStop start function
void functionLedSet(t_BUTTON c) {
	//ledsSet(c);
	if(c == SOUTH )
	canStop();
	else if (c == NORTH)
	canStart();
	else
	canSend(2,c);
}

int main(void)
{	
	#ifdef DEBUG
		stdout = &mystdout;
		init_USART0();
		printf("START MAIN \r");
	#endif
	

	#ifdef DEBUG
		printf("INIT USART done \r");
	#endif
	

	TCCR2A = 7; //timer lance, prediviseur 1024
	TIMSK2 = 1; //interruption locale en overflow
	
	
	#if defined(CC)
		//init CC
		Subsystem0_initialize();
		//init led
		ledsInit();
		// set a default.
		rtU.DesiredSpeed1 = 80;
		rtU.activate1 =TRUE;
		
	#elif defined(WHEEL)
		pwmInit();
		adcInit(&ADCinterrupt);
		ledsInit();
		
	#elif defined(DASHBOARD)
		ledsInit();
		buttonsInit(&functionLedSet);
	#endif // cc//wheel//DASHBOARD


	canInit(&FunctionCANSpeed,&FunctionCANButton,&FunctionCANForce,&FunctionCANSetSpeed,&FunctionCANCCOn);
	canSetBaud();
	canInitMob();
	canInitSend();
	canInitRecieve();
	canStart();
	
    StartOS(OSDEFAULTAPPMODE);
	//ChainTask(stopCANTask);

	
    return 0;
}
