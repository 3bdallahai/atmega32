
#include "STD_TYPES.h"
#include <util/delay.h>

#include	"DIO_interface.h"

#include	"CLCD_config.h"
#include	"CLCD_interface.h"
#include	"CLCD_private.h"




void CLCD_voidSendCommand(u8 copy_u8Command)
{
	/*Set RS Pin to Low for Command */
	DIO_SetPinValue(CLCD_CTRL_Port, CLCD_RS_Pin, DIO_u8PIN_LOW);

	/*Set RW pin to low for Write*/
	DIO_SetPinValue(CLCD_CTRL_Port, CLCD_RW_Pin, DIO_u8PIN_LOW);

	/*Set Command to data pins*/
	DIO_u8SetPortValue(CLCD_Data_Port, copy_u8Command);

	/*Send Enable pulse */
	DIO_SetPinValue(CLCD_CTRL_Port, CLCD_E_Pin, DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_SetPinValue(CLCD_CTRL_Port, CLCD_E_Pin, DIO_u8PIN_LOW);
}

void CLCD_voidSendData (u8 copy_u8Data)
{
	/*Set RS Pin to High for Command */
	DIO_SetPinValue(CLCD_CTRL_Port, CLCD_RS_Pin, DIO_u8PIN_HIGH);

	/*Set RW pin to low for Write*/
	DIO_SetPinValue(CLCD_CTRL_Port, CLCD_RW_Pin, DIO_u8PIN_LOW);

	/*Set Data to data pins*/
	DIO_u8SetPortValue(CLCD_Data_Port, copy_u8Data);

	/*Send Enable pulse */
	DIO_SetPinValue(CLCD_CTRL_Port, CLCD_E_Pin, DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_SetPinValue(CLCD_CTRL_Port, CLCD_E_Pin, DIO_u8PIN_LOW);

}

void CLCD_voidINIT (void)
{
	/*wait for more than 40 ms*/
	_delay_ms(41);

	/*Function Set command:2 lines and 5*8 font size*/
	CLCD_voidSendCommand(0b00111100);

	/*Display on off control: display enable, disable cursor, no blink cursor*/
	CLCD_voidSendCommand(0b00001100);

	/*Clear Display*/
	CLCD_voidSendCommand(1);

}

void CLCD_voidSendString(const char* copy_pcString)
{
	u8 local_u8Counter=0;

	/*Send data to LCD until the string ends*/
	while(copy_pcString[local_u8Counter]!='\0')
	{
		CLCD_voidSendData(copy_pcString[local_u8Counter]);
		local_u8Counter++;
	}

}


void CLCD_voidGotoXY(u8 copy_u8Xposition, u8 copy_u8Yposition)
{
	u8 local_u8address;
	if(copy_u8Xposition==0) local_u8address=copy_u8Yposition;			//first line
	else if(copy_u8Xposition==1) local_u8address=copy_u8Yposition+0x40;	//second line
	CLCD_voidSendCommand(local_u8address+128);	//set bit number 7 to Set DDRAM address command
}

void CLCD_voidWriteSpecialCharacter(u8* copy_pu8pattern,u8 copy_u8PatternNumber,u8 copy_u8Xposition, u8 copy_u8Yposition)
{
	u8 local_u8CGRAMAddress=0, local_u8Iterator;

	/*CGRAM Address, each block is 8 bytes*/
	local_u8CGRAMAddress=copy_u8PatternNumber*8;

	/*Send CGRAM address to the LCD, setting bit 6 and clearing bit 7*/
	CLCD_voidSendCommand(local_u8CGRAMAddress+64);

	/*write array into CGRAM*/
	for(local_u8Iterator=0 ; local_u8Iterator<8; local_u8Iterator++)
	{
		CLCD_voidSendData(copy_pu8pattern[local_u8Iterator]);
	}

	/*return to DDRAM to display pattern*/
	CLCD_voidGotoXY(copy_u8Xposition, copy_u8Yposition);

	/*Display pattern written in CGRAM*/
	CLCD_voidSendData(copy_u8PatternNumber);
}


void CLCD_voidWriteNumber (s32 copy_u32Number)
{
		u8* local_pu8arr[10]={0};
		u8 local_u8counter=0,x;
		if(copy_u32Number==0) CLCD_voidSendData(48);	//send 48 for zero in ASCII
	else
	{

		while(copy_u32Number!=0 )
		{
			local_pu8arr[local_u8counter]=((copy_u32Number%10)+48);
			copy_u32Number=copy_u32Number/10;
			local_u8counter++;
		}
		for(x=0;x<local_u8counter;x++)
		{
			CLCD_voidSendData(local_pu8arr[local_u8counter-x-1]);

		}
	}
}

void CLCD_voidClearDisplay(void)
{
	CLCD_voidSendCommand(1);
}

