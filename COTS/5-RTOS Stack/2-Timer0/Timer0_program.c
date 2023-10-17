/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	RTOS Stack			******************/
/******************		SWC:	TIMER0				******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "Timer0_config.h"
#include "Timer0_private.h"
#include "Timer0_register.h"
#include "Timer0_interface.h"



static void (*Timer0_pvCallBackFunc)(void)=NULL;


void Timer0_voidINIT(void)
{
	/*Initialize time to CTC mode*/
	CLR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);

	/*set compare match value*/
	OCR0=TIMER0_u8COMP_MATCH_VAL;

	/*Set compare match interrupt*/
	SET_BIT(TIMSK,TIMSK_OCIE0);


	/*Select divide by 64 pre-scalar*/
	TCCR0 &= TIMER0_PRESCALER_MASK;
	TCCR0 |= TIMER0_PRESCALER;
	
}


u8 Timer0_u8SetCallBack(void (*Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if(Copy_pvCallBackFunc!=NULL)
	{
		Timer0_pvCallBackFunc= Copy_pvCallBackFunc;

	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}



void __vector_10 (void)	__attribute__((signal));
void __vector_10 (void)
{
if (Timer0_pvCallBackFunc!=NULL)
{
	Timer0_pvCallBackFunc();
}
}

