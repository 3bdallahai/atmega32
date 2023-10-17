/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	HAL 				******************/
/******************		SWC:	LED					******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/

#include  	"STD_TYPES.h"
#include	"BIT_MATH.h"

#include	"DIO_interface.h"
#include	"DIO_register.h"
#include	"DIO_config.h"
#include	"DIO_private.h"

#include 	"LED_private.h"
#include	"LED_interface.h"
#include	"LED_register.h"
#include	"LED_config.h"





u8 LED_u8LedOnOFF(u8 copy_u8Port,u8 copy_u8Pin, u8 copy_u8State)
{
	u8 local_ErrorState=0;

	if(copy_u8State==LED_ON)
	{
		DIO_SetPinValue (copy_u8Port,copy_u8Pin, LED_ON);
	}
	else if(copy_u8State==LED_OFF)
	{
		DIO_SetPinValue (copy_u8Port,copy_u8Pin, LED_OFF);
	}

	else
	{
		local_ErrorState=1;
	}

	return local_ErrorState;

}




u8 LED_u8LedStringOnOff(u8 copy_u8Port, u8 copy_u8State)
{
	u8 local_ErrorState=0;

	if(copy_u8State==LED_STRING_ON) DIO_u8SetPortValue (copy_u8Port, LED_STRING_ON);
	else if(copy_u8State==LED_STRING_OFF) DIO_u8SetPortValue (copy_u8Port, LED_STRING_OFF);
	else local_ErrorState=1;

	return local_ErrorState;

}

u8 LED_u8LedStringcustomize(u8 copy_u8Port, u8 copy_u8Value)
{
	u8 local_ErrorState=0;

		DIO_u8SetPortValue (copy_u8Port, copy_u8Value);



		return local_ErrorState;
}


