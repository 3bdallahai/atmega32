/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	HAL 				******************/
/******************		SWC:	SSD					******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/


#ifndef		SSD_INTERFCE_H_
#define		SSD_INTERFCE_H_

#define SSD_Port		DIO_u8PORTB	  /*choose the port used for SS display Pins*/

#define SSD_EnablePIN0	0
#define SSD_EnablePIN1	1

u8 SSD_u8NumberDisplay(u8 copy_u8Port, u8 copy_u8Number);

#endif
