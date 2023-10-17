/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	MCAL				******************/
/******************		SWC:	WATCHDOG TIMER		******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/

#ifndef		WATCHDOG_REGISTER_H_
#define		WATCHdOG_REGISTER_H_

#define WDTCR 			*((volatile u8*)0x41)
#define WDTCR_WDTOE             4
#define WDTCR_WDE               3
#define WDTCR_WDP2              2
#define WDTCR_WDP1              1
#define WDTCR_WDP0				0

#endif
