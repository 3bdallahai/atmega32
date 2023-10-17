/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	HAL 				******************/
/******************		SWC:	PButton				******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/


#ifndef		PBUTTON_INTERFACE_H_
#define		PBUTTON_INTERFACE_H_

#define PButton_Pressed		0
#define PButton_Unpressed	1


#define		PButton_Port		DIO_u8PORTC
#define		PButton_Pin			DIO_u8PIN5

u8 PButton_voidPbuttonReadValue(u8 copy_u8Port, u8 copy_u8Pin,u8* copy_pu8Value);


#endif
