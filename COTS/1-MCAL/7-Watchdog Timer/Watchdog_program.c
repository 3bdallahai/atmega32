/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	MCAL				******************/
/******************		SWC:	WATCHDOG TIMER		******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "Watchdog_register.h"
#include "Watchdog_interface.h"
#include "Watchdog_config.h"
#include "Watchdog_private.h"






void WDT_voidSleep(u8 copy_u8SleepTimer)
{
	WDTCR &=0b11111000;

	WDTCR |=copy_u8SleepTimer;

}
void WDT_voidEnable(void)
{
	SET_BIT(WDTCR,WDTCR_WDE);
}
void WDT_voidDisable(void)
{
	WDTCR |=0b00011000;

	WDTCR=0;
}
