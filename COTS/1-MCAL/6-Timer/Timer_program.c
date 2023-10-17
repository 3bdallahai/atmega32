/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	MCAL				******************/
/******************		SWC:	TIMER				******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "Timer_config.h"
#include "Timer_private.h"
#include "Timer_register.h"
#include "Timer_interface.h"



static void (*Timer0_pvCallBackFunc)(void)=NULL;

static void (*ICU_pvCallBackFunc)(void)=NULL;


void Timer0_voidINIT(void)
{
	/*Set fast PWM mode*/
	SET_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);

	/*Set compare match interrupt*/
	SET_BIT(TIMSK,TIMSK_OCIE0);

	/*Set Compare Output Mode to non-inverted*/
	CLR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

	OCR0=64;
	/*Select divide by 8 pre-scalar*/
	CLR_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);
}

void Timer0_voidSetCompMatchValue(u8 Copy_u8value)
{
	/*Set compare match value */
	OCR0=Copy_u8value;
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

void Timer1_voidINIT(void)
{
	/*Set Compare Output Mode for Compare unit A to Clear on compare match, set at BOTTOM,*/
//	SET_BIT(TCCR1A,TCCR1A_COM1A1);
//	CLR_BIT(TCCR1A,TCCR1A_COM1A0);

	/*Set wave generate mode Normal mode */
	CLR_BIT(TCCR1B,TCCR1B_WGM13);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1A_WGM10);

//	/*Clock Selection: divide by 8 pre-scaler*/
	TCCR1B&=0b11111000;
	TCCR1B|=0b010;

}

void Timer1_voidSetTimervalue(u16 Copy_u8Value)
{
	TCNT1=Copy_u8Value;
}

u16 Timer1_u16ReadTimerValue(void)
{
	return TCNT1;
}

void Timer1_voidSetCompMatchValueChannelA(u16 Copy_u16value)
{
	OCR1A=Copy_u16value;
}

void Timer1_voidSetICR(u16 Copy_u16value)
{
	ICR1=Copy_u16value;
}

void ICU_voidINIT (void)
{
	SET_BIT(TCCR1B,TCCR1B_ICES1);

	SET_BIT(TIMSK,TIMSK_TICIE1);

}

u8 ICU_u8SetTriggerEdge(u8 Copy_u8Edge)
{
	u8 Local_u8ErrorState=OK;
	if(Copy_u8Edge==ICU_RISING_EDGE)
	{
		SET_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else if(Copy_u8Edge==ICU_FALLING_EDGE)
	{
		CLR_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

void ICU_voidEnableInterrupt(void)
{
	SET_BIT(TIMSK,TIMSK_TICIE1);
}

void ICU_voidDisableInterrupt(void)
{
	CLR_BIT(TIMSK,TIMSK_TICIE1);
}

u16 ICU_u16ReadInputCapture(void)
{
	return ICR1;
}

u8 ICU_u8SetCallBackFunc(void(*copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if(copy_pvCallBackFunc != NULL)
	{
		ICU_pvCallBackFunc=copy_pvCallBackFunc;
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



void __vector_6 (void)	__attribute__((signal));
void __vector_6 (void)
{
	if(ICU_pvCallBackFunc !=NULL)
	{
		ICU_pvCallBackFunc();
	}
}


