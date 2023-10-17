/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	HAL 				******************/
/******************		SWC:	Keypad				******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/


#ifndef		KEYPAD_INTERFACE_H_
#define		KEYPAD_INTERFACE_H_


#define KP_PLUS			11
#define KP_MINUS		12
#define KP_MULT			13
#define KP_DIVIDE		14
#define KP_EQUAL		15
#define KP_START		16



#define KEYPAD_ARR		{{7,8,9,KP_DIVIDE},{4,5,6,KP_MULT},{1,2,3,KP_MINUS},{KP_START,0,KP_EQUAL,KP_PLUS}}

u8 KeyPad_u8GetPressedKey(void);


#endif	
