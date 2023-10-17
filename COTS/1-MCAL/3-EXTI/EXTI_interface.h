/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	MCAL				******************/
/******************		SWC:	EXTI				******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/


#ifndef		EXTI_INTERFACE_H_
#define		EXTI_INTERFACE_H_

#define	ON_CHANGE 		1
#define FALLING_EDGE	2
#define RISING_EDGE		3
#define LOW_LEVEL		4

#define INT0			3
#define INT1			1
#define	INT2			2


void EXTI_voidINT0Init(void);

void EXTI_voidINT1Init(void);

void EXTI_voidINT2Init(void);

/*Description: a function to set the Sense control for INT0 using postbuild configurations
 * Input: copy_u8sense options: 1-LOW_LEVEL
 *                              2-ON_CHANGE
 *                              3-FALLING_EDGE
 *                              4-RISING_EDGE
 * Output: Error State with type u8
 *   */
u8 EXTI_u8INT0SetSenseControl(u8 copy_u8sense);

u8 EXTI_u8INT1SetSenseControl(u8 copy_u8sense);

u8 EXTI_u8INT2SetSenseControl(u8 copy_u8sense);

u8 EXTI_u8INTEnable(u8 copy_u8INT);

u8 EXTI_u8INTDisable(u8 copy_u8INT);

u8 EXTI_u8INT0SetCallBack(void (*copy_pvoidINT0Func)(void));

u8 EXTI_u8INT1SetCallBack(void (*copy_pvoidINT1Func)(void));

u8 EXTI_u8INT2SetCallBack(void (*copy_pvoidINT2Func)(void));




#endif
