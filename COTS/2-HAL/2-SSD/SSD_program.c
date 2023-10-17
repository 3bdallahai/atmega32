/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	HAL 				******************/
/******************		SWC:	SSD					******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/

#include  	"STD_TYPES.h"

#include	"DIO_interface.h"
#include	"DIO_register.h"
#include	"DIO_config.h"
#include	"DIO_private.h"

#include	"SSD_interface.h"
#include	"SSD_register.h"
#include	"SSD_config.h"
#include	"SSD_private.h"


u8 SSD_u8NumberDisplay(u8 copy_u8Port, u8 copy_u8Number)
{
	u8 local_ErrorState=0;
	
	if (copy_u8Number<10)
	{

		DIO_u8SetPortValue(copy_u8Port, SSD_u8arr[copy_u8Number]);
	}
	else local_ErrorState=1;
	
	return local_ErrorState;
}
