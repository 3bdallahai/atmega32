/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	HAL 				******************/
/******************		SWC:	LED					******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/


#ifndef		LED_INTERFCE_H_
#define		LED_INTERFCE_H_


#define	LED_ON	DIO_u8PIN_HIGH
#define	LED_OFF	DIO_u8PIN_LOW

#define	LED_STRING_ON	0xff
#define	LED_STRING_OFF	0


u8 LED_u8LedOnOFF(u8 copy_u8Port,u8 copy_u8Pin, u8 copy_u8State);



u8 LED_u8LedStringOnOff(u8 copy_u8Port, u8 copy_u8State);


u8 LED_u8LedStringcustomize(u8 copy_u8Port, u8 copy_u8Value);






#endif
