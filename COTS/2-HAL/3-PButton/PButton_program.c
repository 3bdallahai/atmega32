/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	HAL 				******************/
/******************		SWC:	PButton				******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/



#include  	"STD_TYPES.h"
#include <util/delay.h>

#include	"DIO_interface.h"
#include	"DIO_register.h"
#include	"DIO_config.h"
#include	"DIO_private.h"

#include	"PButton_interface.h"
#include	"PButton_private.h"



u8 PButton_voidPbuttonReadValue(u8 copy_u8Port, u8 copy_u8Pin,u8* copy_pu8Value)
{
	u8 local_u8ErrorState=0;
	if(copy_pu8Value==NULL) local_u8ErrorState=2;
	else
	{
		DIO_u8GetPinValue(copy_u8Port,  copy_u8Pin,  copy_pu8Value);
		_delay_ms(250);
	}


		return local_u8ErrorState;
}
