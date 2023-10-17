/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	RTOS Stack			******************/
/******************		SWC:	RTOS				******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/

#include "STD_TYPES.h"

#include "Timer_interface.h"
#include "GIE_interface.h"

#include "RTOS_private.h"
#include "RTOS_config.h"
#include "RTOS_interface.h"

Task_t SystemTask[TASK_NUM]={{NULL}};

void RTOS_voidStart(void)
{
	Timer0_u8SetCallBack(&voidScheduler);
	GIE_vidGIEEnable();
	Timer0_voidINIT();
}

u8 RTOS_voidCreateTask(u8 Copy_u8Priority, u16 Copy_u16Periodicity, void (*Copy_pvTaskFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	/*Check if the required priority is empty or not */
	if(SystemTask[Copy_u8Priority].TaskFunc==NULL)
	{
		SystemTask[Copy_u8Priority].Periodicity=Copy_u16Periodicity;
		SystemTask[Copy_u8Priority].TaskFunc=Copy_pvTaskFunc;
		SystemTask[Copy_u8Priority].state=TASK_RESUMED;
	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

static void voidScheduler (void)
{
	static u16 Local_u16TickCounter=0;
	u8 Local_u8TaskCounter;

	Local_u16TickCounter++;

	/*Loop all the tasks to check their periodicity*/
	for(Local_u8TaskCounter=0; Local_u8TaskCounter<TASK_NUM; Local_u8TaskCounter++)
	{
		/*check if the task is suspended or resumed*/
		if(SystemTask[Local_u8TaskCounter].state == TASK_RESUMED)
		{
			if ((Local_u16TickCounter % SystemTask[Local_u8TaskCounter].Periodicity) == 0)
			{
				/*Invoke the task function*/
				if ((SystemTask[Local_u8TaskCounter].TaskFunc != NULL_POINTER))
				{
					SystemTask[Local_u8TaskCounter].TaskFunc();
				}
				else
				{
					/*do nothing*/
				}
			}
		}
		else
		{
			/*task is suspended, do nothing*/
		}
	}

}

void RTOS_voidDeleteTask(u8 Copy_u8Priority)
{
	SystemTask[Copy_u8Priority].TaskFunc=NULL;
}

void RTOS_voidSuspendTask(u8 Copy_u8Priority)
{
	SystemTask[Copy_u8Priority].state=TASK_SUSPENDED;
}

void RTOS_voidResumeTask(u8 Copy_u8Priority)
{
	SystemTask[Copy_u8Priority].state=TASK_RESUMED;
}
