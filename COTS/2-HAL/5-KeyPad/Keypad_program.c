/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	HAL 				******************/
/******************		SWC:	Keypad				******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/

#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "Keypad_config.h"
#include "Keypad_interface.h"
#include "Keypad_private.h"


u8 KeyPad_u8GetPressedKey(void)
{
	u8 Local_u8Pressed_key=NO_PRESSED_KEY, Local_u8ColumnIdx,Local_u8RowIdx, Local_u8PinState;
	static u8 Local_u8KeyPadArr[ROW_NUMBER][COLUMN_NUMBER]= KEYPAD_ARR;
	static u8 Local_u8KeyPadColumnArr[COLUMN_NUMBER]={KEYPAD_COLUMN0_PIN,KEYPAD_COLUMN1_PIN,KEYPAD_COLUMN2_PIN,KEYPAD_COLUMN3_PIN};
	static u8 Local_u8KEyPadRowArr[ROW_NUMBER]={KEYPAD_ROW0_PIN,KEYPAD_ROW1_PIN,KEYPAD_ROW2_PIN,KEYPAD_ROW3_PIN};

	for (Local_u8ColumnIdx=0;Local_u8ColumnIdx< COLUMN_NUMBER ;Local_u8ColumnIdx++)
	{
		/*Activate current column*/
		DIO_SetPinValue(KEYPAD_PORT, Local_u8KeyPadColumnArr[Local_u8ColumnIdx], DIO_u8PIN_LOW);

		for (Local_u8RowIdx=0; Local_u8RowIdx<ROW_NUMBER; Local_u8RowIdx++)
		{
			/*Read the current row*/
			DIO_u8GetPinValue(KEYPAD_PORT, Local_u8KEyPadRowArr[Local_u8RowIdx], &Local_u8PinState);

			/*check if switch is pressed*/
			if(DIO_u8PIN_LOW==Local_u8PinState)
			{
				Local_u8Pressed_key=(u8)Local_u8KeyPadArr[Local_u8RowIdx][Local_u8ColumnIdx];

				while(DIO_u8PIN_LOW==Local_u8PinState)
				{
					DIO_u8GetPinValue(KEYPAD_PORT, Local_u8KEyPadRowArr[Local_u8RowIdx], &Local_u8PinState);

				}

				return Local_u8Pressed_key;
			}
		}
		/*deactivate current column*/
		DIO_SetPinValue(KEYPAD_PORT, Local_u8KeyPadColumnArr[Local_u8ColumnIdx], DIO_u8PIN_HIGH);

	}

	return Local_u8Pressed_key;
}
