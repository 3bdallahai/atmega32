/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	MCAL				******************/
/******************		SWC:	ADC					******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/


#ifndef		ADC_INTERFACE_H_
#define		ADC_INTERFACE_H_

typedef struct
{
	u8* 	Channel;
	u16* 	Results;
	u8		Size;
	void (*NotifactionFunc)(void);
}Chain_t;

void ADC_voidINIT(void);

u8 ADC_u8StartConversionSynch(u8 copy_u8Channel, u8* copy_pu8Reading);

u8 ADC_u8StartConversionAsynch(u8 copy_u8Channel, u8* copy_pu8Reading, void(*copy_pvNotifactionFunc)(void));

u8 ADC_u8mapping(f32 Copy_u8ADCReading, f32 Copy_u8TopScaleValue, f32 Copy_u8LowScaleValue);

u8 ADC_u8StartChainAsynch(Chain_t* Copy_Chain);

#endif
