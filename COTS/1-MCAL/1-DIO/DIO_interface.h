/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	MCAL				******************/
/******************		SWC:	DIO					******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/


#ifndef		DIO_INTERFCE_H_
#define		DIO_INTERFCE_H_


#define	DIO_u8PIN_HIGH			1 
#define DIO_u8PIN_LOW			0


#define DIO_u8PORT_HIGH			0xff
#define DIO_u8PORT_LOW			0

#define DIO_u8PORTA				1
#define DIO_u8PORTB				2
#define DIO_u8PORTC				3
#define	DIO_u8PORTD				4

#define DIO_u8PIN0				0
#define DIO_u8PIN1				1
#define DIO_u8PIN2				2
#define DIO_u8PIN3				3
#define DIO_u8PIN4				4
#define DIO_u8PIN5				5
#define DIO_u8PIN6				6
#define DIO_u8PIN7				7





u8	DIO_SetPinValue (u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8Value);

u8	DIO_u8SetPortValue(u8 copy_u8Port,  u8 copy_u8Value);

u8 DIO_u8TogglePin(u8 copy_u8Port, u8 copy_u8Pin);

u8	DIO_u8GetPinValue(u8 copy_u8Port, u8 copy_u8Pin, u8* copy_pu8Value);


#endif	
