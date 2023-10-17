/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	MCAL				******************/
/******************		SWC:	TIMER				******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/


#ifndef		TIMER_INTERFACE_H_
#define		TIMER_INTERFACE_H_ 

#define ICU_RISING_EDGE		1
#define ICU_FALLING_EDGE	0

void Timer0_voidINIT(void);

u8 Timer0_u8SetCallBack(void (*Copy_pvCallBackFunc)(void));

void Timer0_voidSetCompMatchValue(u8 Copy_u8value);

void Timer1_voidINIT(void);

void Timer1_voidSetCompMatchValueChannelA(u16 Copy_u8value);

void Timer1_voidSetICR(u16 Copy_u8value);

void Timer1_voidSetTimervalue(u16 Copy_u8Value);

u16 Timer1_u16ReadTimerValue(void);

void ICU_voidINIT (void);

u8 ICU_voidSetTriggerEdge(u8 Copy_u8Edge);

void ICU_voidDisableInterrupt(void);

void ICU_voidEnableInterrupt(void);

u16 ICU_u16ReadInputCapture(void);

u8 ICU_u8SetCallBackFunc(void(*copy_pvCallBackFunc)(void));

#endif
