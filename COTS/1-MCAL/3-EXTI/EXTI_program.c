/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	MCAL				******************/
/******************		SWC:	EXTI				******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"
#include "EXTI_register.h"


void (*EXTI_pvoidINT0Func)(void)=NULL;
void (*EXTI_pvoidINT1Func)(void)=NULL;
void (*EXTI_pvoidINT2Func)(void)=NULL;

void EXTI_voidINT0Init(void)
{

	/*Check on Sense Control*/
#if	  INT0_SENSE==LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC01);
	CLR_BIT(MCUCR,MCUCR_ISC00);

#elif INT0_SENSE==ON_CHANGE
	CLR_BIT(MCUCR,MCUCR_ISC01);
	SET_BIT(MCUCR,MCUCR_ISC00);

#elif INT0_SENSE==FALLING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC01);
	CLR_BIT(MCUCR,MCUCR_ISC00);

#elif INT0_SENSE==RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC01);
	SET_BIT(MCUCR,MCUCR_ISC00);

#else
#error "wrong INT0_SENSE option"
#endif


#if INT0_INITIAL_STATE==ENABLED
	SET_BIT(GICR,GICR_INT0);

#elif INT0_INITIAL_STATE==DISABLED
	CLR_BIT(GICR,GICR_INT0);

#else
#error "wrong INT0_INTIAL_STATE option"

#endif

}

void EXTI_voidINT1Init(void)
{
	/*Check on Sense Control*/
#if	  INT1_SENSE==LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC11);
	CLR_BIT(MCUCR,MCUCR_ISC10);

#elif INT1_SENSE==ON_CHANGE
	CLR_BIT(MCUCR,MCUCR_ISC11);
	SET_BIT(MCUCR,MCUCR_ISC10);

#elif INT1_SENSE==FALLING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC11);
	CLR_BIT(MCUCR,MCUCR_ISC10);

#elif INT1_SENSE==RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC11);
	SET_BIT(MCUCR,MCUCR_ISC10);

#else
#error "wrong INT1_SENSE option"
#endif


#if INT1_INITIAL_STATE==ENABLED
	SET_BIT(GICR,GICR_INT1);

#elif INT1_INITIAL_STATE==DISABLED
	CLR_BIT(GICR,GICR_INT1);

#else
#error "wrong INT0_INTIAL_STATE option"

#endif

}

void EXTI_voidINT2Init(void)
{
	/*Check on Sense Control*/
#if	 INT2_SENSE==FALLING_EDGE
	CLR_BIT(MCUCSR,MCUCR_ISC2);


#elif INT2_SENSE==RISING_EDGE
	SET_BIT(MCUCSR,MCUCR_ISC2);

#else
#error "wrong INT2_SENSE option"
#endif


#if INT2_INITIAL_STATE==ENABLED
	SET_BIT(GICR,GICR_INT2);

#elif INT2_INITIAL_STATE==DISABLED
	CLR_BIT(GICR,GICR_INT2);

#else
#error "wrong INT0_INTIAL_STATE option"

#endif
}


u8 EXTI_u8INT0SetSenseControl(u8 copy_u8sense)
{
	u8 Local_u8ErrorState=OK;
	switch(copy_u8sense)
	{
	case FALLING_EDGE:SET_BIT(MCUCR,MCUCR_ISC01); CLR_BIT(MCUCR,MCUCR_ISC00); break;
	case RISING_EDGE: SET_BIT(MCUCR,MCUCR_ISC01); SET_BIT(MCUCR,MCUCR_ISC00); break;
	case LOW_LEVEL: CLR_BIT(MCUCR,MCUCR_ISC01);	CLR_BIT(MCUCR,MCUCR_ISC00);	break;
	case ON_CHANGE:	CLR_BIT(MCUCR,MCUCR_ISC01); SET_BIT(MCUCR,MCUCR_ISC00);	break;
	default: Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

u8 EXTI_u8INT1SetSenseControl(u8 copy_u8sense)
{
	u8 Local_u8ErrorState=OK;
	switch(copy_u8sense)
	{
	case FALLING_EDGE:SET_BIT(MCUCR,MCUCR_ISC11); CLR_BIT(MCUCR,MCUCR_ISC10); break;
	case RISING_EDGE: SET_BIT(MCUCR,MCUCR_ISC11); SET_BIT(MCUCR,MCUCR_ISC10); break;
	case LOW_LEVEL: CLR_BIT(MCUCR,MCUCR_ISC11);	CLR_BIT(MCUCR,MCUCR_ISC10);	break;
	case ON_CHANGE:	CLR_BIT(MCUCR,MCUCR_ISC11); SET_BIT(MCUCR,MCUCR_ISC10);	break;
	default: Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

u8 EXTI_u8INT2SetSenseControl(u8 copy_u8sense)
{
	u8 Local_u8ErrorState=OK;
	switch(copy_u8sense)
	{
	case FALLING_EDGE:CLR_BIT(MCUCSR,MCUCR_ISC2); break;
	case RISING_EDGE: SET_BIT(MCUCSR,MCUCR_ISC2); break;

	default: Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}


u8 EXTI_u8INTEnable(u8 copy_u8INT)
{
	u8 Local_u8Errorstate=OK;
switch (copy_u8INT)
{
case INT0: SET_BIT(GICR,GICR_INT0); break;
case INT1: SET_BIT(GICR,GICR_INT1); break;
case INT2: SET_BIT(GICR,GICR_INT2); break;
default: Local_u8Errorstate=NOK;
}
return Local_u8Errorstate;
}

u8 EXTI_u8INTDisable(u8 copy_u8INT)
{
	u8 Local_u8Errorstate=OK;
switch (copy_u8INT)
{
case INT0: CLR_BIT(GICR,GICR_INT0); break;
case INT1: CLR_BIT(GICR,GICR_INT1); break;
case INT2: CLR_BIT(GICR,GICR_INT2); break;
default: Local_u8Errorstate=NOK;
}
return Local_u8Errorstate;
}





u8 EXTI_u8INT0SetCallBack(void (*copy_pvoidINT0Func)(void))
{
	u8 Local_u8ErrorState=OK;

	if(copy_pvoidINT0Func!=NULL)
	{
		EXTI_pvoidINT0Func=copy_pvoidINT0Func;
	}
	else
	{
		Local_u8ErrorState==NULL_POINTER;
	}

	return Local_u8ErrorState;
}


u8 EXTI_u8INT1SetCallBack(void (*copy_pvoidINT1Func)(void))
{
	{
		u8 Local_u8ErrorState=OK;

		if(copy_pvoidINT1Func!=NULL)
		{
			EXTI_pvoidINT1Func=copy_pvoidINT1Func;
		}
		else
		{
			Local_u8ErrorState==NULL_POINTER;
		}

		return Local_u8ErrorState;
	}

}

u8 EXTI_u8INT2SetCallBack(void (*copy_pvoidINT2Func)(void))
{
	{
		u8 Local_u8ErrorState=OK;

		if(copy_pvoidINT2Func!=NULL)
		{
			EXTI_pvoidINT2Func=copy_pvoidINT2Func;
		}
		else
		{
			Local_u8ErrorState==NULL_POINTER;
		}

		return Local_u8ErrorState;
	}

}


/*ISR of INT0*/
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	if (EXTI_pvoidINT0Func!=NULL)	EXTI_pvoidINT0Func();
	else
	{
		/*Do nothing*/
	}

}


/*ISR of INT1*/
void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	if (EXTI_pvoidINT1Func!=NULL)	EXTI_pvoidINT1Func();
	else
	{
		/*Do nothing*/
	}

}

void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	if (EXTI_pvoidINT2Func!=NULL)	EXTI_pvoidINT2Func();
		else
		{
			/*Do nothing*/
		}
}
