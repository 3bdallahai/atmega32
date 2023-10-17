/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	MCAL				******************/
/******************		SWC:	PORT				******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/

#include "STD_TYPES.h"

#include "PORT_config.h"
#include "PORT_private.h"
#include "PORT_interface.h"
#include "PORT_register.h"		


void PORT_voidInit(void)
{
	DDRA=PORTA_DIR;
	DDRB=PORTB_DIR;
	DDRC=PORTC_DIR;
	DDRD=PORTD_DIR;
	
	PORTA= PORTA_INTIAL_VALUE;
	PORTB= PORTB_INTIAL_VALUE;
    PORTC= PORTC_INTIAL_VALUE;
    PORTD= PORTD_INTIAL_VALUE;
	
	
}