/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	HAL 				******************/
/******************		SWC:	CLCD				******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/


#ifndef		CLCD_INTERFACE_H_
#define		CLCD_INTERFACE_H_

void CLCD_voidSendCommand(u8 copy_u8Command);

void CLCD_voidSendData (u8 copy_u8Data);

void CLCD_voidINIT (void);

void CLCD_voidSendString(const char* copy_pcString);

void CLCD_voidGotoXY(u8 copy_u8Xposition, u8 copy_u8Yposition);

void CLCD_voidWriteSpecialCharacter(u8* copy_pu8pattern,u8 copy_u8PatternNumber,u8 copy_u8Xposition, u8 copy_u8Yposition);

void CLCD_voidWriteNumber (s32 copy_u32Number);

void CLCD_voidClearDisplay(void);


#endif	
