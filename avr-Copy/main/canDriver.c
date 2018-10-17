/*
 * canDriver.c
 *
 * Created: 16/05/2018 14:57:09
 *  Author: Kris
 */ 
#include "headers/canDriver.h"


void canInitSendOne(uint16_t can_id, char mob, char length);
void canInitReceiveOne(uint16_t can_id, char mob, char length);


/*! \brief initialize the can driver.
 *	* initialize function pointers
 *	* do software reset
 *	* enable interrupts
 *
 */
void canInit(void* FunctionCANSpeed, void* FunctionCANButton, void* FunctionCANForce, void* FunctionCANSetSpeed, void* FunctionCANCCOn){
		stdout = &mystdout;
		init_USART0();
		printf("START MAIN \r");
		
	functionCANSpeed = FunctionCANSpeed;
	functionCANButton = FunctionCANButton;
	functionCANForce = FunctionCANForce;
	functionCANSetSpeed = FunctionCANSetSpeed;
	functionCANCCOn = FunctionCANCCOn;
		
	
	CANGCON |= (1 << SWRES); //swres software reset
	
	//enable interrupt for all mobs
	CANIE1 = 0x7F;
	CANIE2 = 0xFF;
}


/*!
 * \brief set the baud rate for the can        
 *  
 * Fclk = 8MHz
 * baudrate = 125 kbps
 * Tq = 0.5                                                      
 */
void canSetBaud(void){
	CANBT1 = 0x06;
	CANBT2 = 0x0C; // of 0x04
	CANBT3 = 0x37;
}

/*!
 * \brief initialize the different MOBs
 * alles gewoon resetten ahv for'ke
 * canpage selecteren MOB
 * CANCDMOB resetten
 * CANSTMOB resetten
 * loopen over messages en op 0 zetten
 * * DLC3:0: Data Length Code
 *		* aantal bytes
 * * gebruik IDE: 0 ( CAN standard rev 2.0 A (identifiers length = 11 bits) )
 */
void canInitMob(void){
	int i;
	for(i = 0; i < 15; i++) {
		CANPAGE = i << 4; //select mob
		
		CANCDMOB = 0; //reset
		CANSTMOB = 0;
		
		//IDT, RTRTAG, RBnTAG
		CANIDT1 = 0;                        //ID
		CANIDT2 = 0;
		CANIDT3 = 0;
		CANIDT4 = 0;
		//IDMSK, IDEMSK, RTRMSK
		CANIDM1 = 0;                        //get all messages
		CANIDM2 = 0;                        //1 = check bit
		CANIDM3 = 0;                        //0 = ignore bit
		CANIDM4 = 0; //(1<<IDEMSK); 		// do not ignore standard frames
		CANMSG = 0;
		/*if(i >= 5)
		CANCDMOB = (1 << CONMOB1) | (1 << IDE);
		else
		CANCDMOB = 0; //(1 << IDE);*/
	}
	
}

/*!
 * \brief 
 * * klaarzetten om te sturen
 * * versturen ahv interrupt
 * * static mob toekennen
 *		* rtr en ide mask enable
 *		* geen extended id
 * * lengte bericht er in steken
 * * afhankelijk van bordje
 * * CANCDMOB
 *		* CONMOB[1:0] => 00 disable, 01 enable Tx, 10 enable Rx
 *	* CANIDT1, CANIDT2, CANIDT3, and CANIDT4
 *		* IDT: zelf id invullen
 */
void canInitSend(void){
	uint32_t can_id;
	char mob;
	#if defined(WHEEL)
		//wheelSpeed	ID: 1 length: 1
		can_id = 0x00000001;       // message ID = 1
		mob = 0xA0;
		canInitSendOne(can_id, mob, 1);
	#elif defined(CC)
		//force			ID: 3 length: 2
		can_id = 0x00000003;       // message ID = 3
		mob = 0xC0; 			   // mob12
		canInitSendOne(can_id, mob, 2 );
	
		//CCON			ID: 4 length: 1
		can_id = 0x00000004;       // message ID = 4
		mob = 0xD0;					//MOb13 select
		canInitSendOne(can_id, mob, 1 );
	#elif defined(DASHBOARD)
		//printf("lol");
		//buttons		ID: 2 length: 1
		can_id = 0x00000002;       // message ID = 1
		mob = 0xB0; 			   // mob11
		canInitSendOne(can_id, mob, 1 );
	#endif // this_ECU= DASHBOARD		
	/*
	switch(this_ECU) {
		case WHEEL:
		//wheelSpeed	ID: 1 length: 1
		can_id = 0x00000001;       // message ID = 1
		mob = 0xA0;
		canInitSendOne(can_id, mob, 1);
		
		break;
		case CC:
		//force			ID: 3 length: 2
		can_id = 0x00000003;       // message ID = 3
		mob = 0xC0; 			   // mob12
		canInitSendOne(can_id, mob, 2 );
		
		//CCON			ID: 4 length: 1
		can_id = 0x00000004;       // message ID = 4
		mob = 0xD0;					//MOb13 select
		canInitSendOne(can_id, mob, 1 );
		
		break;
		case DASHBOARD:
		//buttons		ID: 2 length: 1
		can_id = 0x00000002;       // message ID = 1
		mob = 0xB0; 			   // mob11
		canInitSendOne(can_id, mob, 1 );
		
		break;
		default:
		break;
	}*/
}


void canInitSendOne(uint16_t can_id, char mob, char length) {
	CANPAGE = mob;			//MOb11 select
	CANSTMOB = 0x00;		//clear flag
	CANIDT4 = 0x00;			//RTRTAG = 0 "Data Frame"
	CANIDT3 = 0x00;
	CANIDT2 = (uint8_t)(can_id << 5);			// set ID Tag
	CANIDT1 = (uint8_t)(can_id >> 3);
	CANIDM1 = 0x00;			// no mask
	CANIDM2 = 0x00;
	CANIDM3 = 0x00;
	CANIDM4 = 0x00;
	CANCDMOB = 0x40 | (length & 0x0F); // enable transmission + set length of message

}
/*!
 * \brief can klaarzetten om berichten te ontvangen
 * * klaarzetten om berichten te versturen
 * * interrupt
 * * static mob toekennen
 *		* nodig om register te schrijven
 * 
 * * CANCDMOB
 *		* CONMOB[1:0] => 00 disable, 01 enable Tx, 10 enable Rx
 * IDT
 * IDMSK
 * IDE
 * IDEMSK
 * RTRTAG x
 * RTRMSK
 * DLC
 * RBnTAG x
 */
void canInitRecieve(void){

	uint32_t can_id;
	char mob;
	#if defined(CC)
	//wheelSpeed	ID: 1 length: 1		ECU2 en ECU3
	can_id = 0x00000001;   // which ID to accept
	mob = 0x10; // MOb0 Select
	canInitReceiveOne(can_id, mob, 1);
	
	//buttons	ID: 2 length: 1		ECU2 en ECU3
	can_id = 0x00000002;   // which ID to accept
	mob = 0x20; // MOb1 Select
	canInitReceiveOne(can_id, mob, 1);
	
	#elif defined(DASHBOARD)
	//wheelSpeed	ID: 1 length: 1
	can_id = 0x00000001;   // which ID to accept
	mob = 0x10; // MOb0 Select
	canInitReceiveOne(can_id, mob, 1);
	
	//force	ID: 3 length: 2
	can_id = 0x00000003;   // which ID to accept
	mob = 0x30; // MOb0 Select
	canInitReceiveOne(can_id, mob, 2);
	
	//CCOn	ID: 4 length: 1
	can_id = 0x00000004;   // which ID to accept
	mob = 0x40; // MOb0 Select
	canInitReceiveOne(can_id, mob, 1);
	#endif // this_ECU == DASHBOARD
	
	/*switch(this_ECU) {
		case WHEEL:
			break;
		case CC:
		//wheelSpeed	ID: 1 length: 1		ECU2 en ECU3
			can_id = 0x00000001;   // which ID to accept
			mob = 0x10; // MOb1 Select
			canInitReceiveOne(can_id, mob, 1);
		
			//buttons	ID: 2 length: 1		ECU2 en ECU3
			can_id = 0x00000002;   // which ID to accept
			mob = 0x20; // MOb1 Select
			canInitReceiveOne(can_id, mob, 1);
		
			break;
		case DASHBOARD:
			//wheelSpeed	ID: 1 length: 1
			can_id = 0x00000001;   // which ID to accept
			mob = 0x10; // MOb1 Select
			canInitReceiveOne(can_id, mob, 1);
		
			//force	ID: 3 length: 2
			can_id = 0x00000003;   // which ID to accept
			mob = 0x30; // MOb3 Select
			canInitReceiveOne(can_id, mob, 2);
		
			//CCOn	ID: 4 length: 1
			can_id = 0x00000004;   // which ID to accept
			mob = 0x40; // MOb4 Select
			canInitReceiveOne(can_id, mob, 1);
		
			break;
		default:
			break;
	
	}*/
}

void canInitReceiveOne(uint16_t can_id , char mob, char length) {
	CANPAGE = mob; // MOb Select
	CANIDT4 = 0x00;                     //set ID Tag
	CANIDT3 = 0x00;
	CANIDT2 = (uint8_t)(can_id << 5);
	CANIDT1 = (uint8_t)(can_id >> 3);
	CANIDM1 = 0xFF;                    // accept only this ID
	CANIDM2 = 0xFF;
	CANIDM3 = 0x00;
	CANIDM4 = (1 << RTRMSK);
	//char data= CANMSG;                     //Get data
	CANCDMOB = 0x80 | (length & 0x0F);		//enable reception .... RPLV=0 ..... IDE=0 "11-bit" ... data length =1 byte
	CANSTMOB = 0x00;		// clear flag

}
/*!
 * \brief message versturen 
 *	* opbouw bericht
 *	* data inshiften
 *	* send interrupt enablen
 *	* CANIDT1, CANIDT2, CANIDT3, and CANIDT4
 *		* IDT: wordt automatisch ingevuld
 */
void canSend(char id, uint16_t value){
	switch(id){
		case 1:
			CANPAGE = 0xA0;						//MOb10 select
			CANMSG = (uint16_t)(value);			//data i want to send
			break;
		case 2:
			CANPAGE = 0xB0;						//MOb10 select
			CANMSG = (uint16_t)(value);			//data i want to send
			break;
		case 3:
			CANPAGE = 0xC0;						//MOb10 select
			CANMSG = (uint16_t)(value >> 8);	//data i want to send
			CANMSG = (uint16_t)(value);
			break;
		case 4:
			CANPAGE = 0xD0;						//MOb10 select
			CANMSG = (uint16_t)(value);			//data i want to send
			break;
		case 5:
			CANPAGE = 0xE0;						//MOb10 select
			CANMSG = (uint16_t)(value);			//data i want to send
			break;
	}
	CANCDMOB |= (1 << CONMOB0);	
}

/*!
 * \brief stoppen van de can
 * * pas wanneer er niet verstuurd/ontvangen wordt
 * * CANCDMOB
 *		* CONMOB[1:0] => 00 disable, 01 enable Tx, 10 enable Rx
 */
void canStop(void){
	while(CANGIT & (1 << CANIT)){}
		CANGIE = ~(~CANGIE | (1 << ENIT)| (1 << ENRX) | (1 << ENTX)); // all interrupts disabled
		CANGCON = ~(~CANGCON | (1 << ENASTB)); // disable CAN controller*/
}
/*!
 * \brief can opstarten
 * interrupts en controller enablen.
 */
void canStart(void){
	CANGIE = CANGIE | (1 << ENIT)| (1 << ENRX) | (1 << ENTX); // all interrupts enabled
	// activate CAN controller
	CANGCON |= (1 << ENASTB);
}


ISR(CANIT_vect) {
	CANGIT = ~(~CANGIT | (1 << CANIT));
	unsigned char temp;
	temp = CANPAGE;
	CANPAGE = CANHPMOB;
	
	char data1, data2 = 0x00; 

	if (CANSTMOB & (1 << RXOK))
	{
		//printf("voor de switch: %d \n", CANPAGE >> 4);
		switch(CANPAGE >> 4) {
			case 1:
				data1 = CANMSG;
				functionCANSpeed(data1);
				break;
			case 2:
				data1 = CANMSG;
				functionCANButton(data1);
				break;
			case 3:
				data1 = CANMSG;
				CANPAGE |= 1 << INDX0;
				data2 = CANMSG;
				uint16_t data = (uint16_t)(data1 << 8) + (uint16_t)(data2);
				functionCANForce(data);
				break;
			case 4:
				data1 = CANMSG;
				functionCANSetSpeed(data1);
				break;
			case 5:
				data1 = CANMSG;
				functionCANCCOn(data1);
				break;
		}
		
		CANCDMOB |= 1 << CONMOB1;
	}
	else if (CANSTMOB & (1 << TXOK))
	{
		//printf("Tx ok \n");
		
	}
	else
	{
		
	}	
	CANSTMOB = 0x00; // clear MOb1 RXOK Interrupt Flag
	CANPAGE = temp;
}