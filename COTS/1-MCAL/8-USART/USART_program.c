/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	MCAL				******************/
/******************		SWC:	USART				******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "USART_register.h"
#include "USART_config.h"
#include "USART_private.h"
#include "USART_interface.h"



void USART_voidINIT(void)
{
	u8 Local_u8UCSRCValue=0;

	SET_BIT(Local_u8UCSRCValue,UCSRC_URSEL);
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UMSEL);	//Asynchronous
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UPM0);		// no parity
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UPM1);
	CLR_BIT(Local_u8UCSRCValue,UCSRC_USBS);		//1 stop bit,
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);	//8 bits size
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	UCSRC=Local_u8UCSRCValue;
	UBRRL=51;					//Select baud rate to 9600;
	SET_BIT(UCSRB,UCSRB_RXEN);		//Receiver Enable
	SET_BIT(UCSRB,UCSRB_TXEN);		//Transmitter Enable
}
void USART_voidSend(u8 copy_u8Data)
{
	while((GET_BIT(UCSRA,UCSRA_UDRE))==0);
	UDR= copy_u8Data;


}
u8 USART_u8Receive(void)
{
	while((GET_BIT(UCSRA,UCSRA_RXC))==0);

	return UDR;


}
