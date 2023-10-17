/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	MCAL				******************/
/******************		SWC:	ADC					******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_config.h"
#include "ADC_private.h"
#include "ADC_register.h"
#include "ADC_interface.h"


static u8* ADC_u8Reading=NULL;
static void(*ADC_pvCallBackNotifactionFunc)(void)=NULL;

static	u8*  ADC_puChainChannelArr=NULL;		//global variable to carry chain array
static	u16* ADC_pu16ChainResultArr=NULL;		//global variable to carry results array
static	u8	 ADC_u8ChainSize=0;					//global variable to carry number of channels
static	u8 	 ADC_u8ChainConversionIndex=0;		//global variable to carry the current conversion index
static	u8 	 ADC_u8BusyState=IDLE;
static	u8   ADC_u8ISRSorce;


 void ADC_voidINIT(void)
{
	/*AVCC as reference voltage*/
	CLR_BIT(ADMUX,ADMUX_REFS1);
	SET_BIT(ADMUX,ADMUX_REFS0);

	/*Activate left adjust result*/
	SET_BIT(ADMUX,ADMUX_ADLAR);

	/*Set prescaler to divide by 128 */
	SET_BIT(ADCSRA,ADCSRA_ADPS2);
	SET_BIT(ADCSRA,ADCSRA_ADPS1);
	SET_BIT(ADCSRA,ADCSRA_ADPS0);

	/*ADC ENable*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);

}
u8 ADC_u8StartConversionSynch(u8 copy_u8Channel, u8* copy_pu8Reading)
{
	u32 Local_u32Counter=0;
	u8 Local_u8ErrorState=OK;
	if(ADC_u8BusyState==IDLE)
	{
		if (copy_pu8Reading==NULL)
		{
			Local_u8ErrorState==NULL_POINTER;
		}
		else
		{
			/*make ADC busy to work until idle*/
			ADC_u8BusyState= BUSY;
			/*Clear MUX bits in ADMUX register*/
			ADMUX &= 0b11100000;

			/*Set the required channel into MUX bits*/
			ADMUX |= copy_u8Channel;

			/*Start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*polling until the conversion flag is set or counter reaches timeout */
			while((GET_BIT(ADCSRA,ADCSRA_ADIF)==0) &&(Local_u32Counter != ADC_TIMEOUT))
			{
				Local_u32Counter++;
			}

			if (Local_u32Counter==ADC_TIMEOUT)
			{
				// loop broke due to timeout
				Local_u8ErrorState=NOK;
			}
			else
			{
				// loop broke because conversion flag is raised
				*copy_pu8Reading=ADCH;

				/*make ADC idle because it is finished*/
				ADC_u8BusyState=IDLE;
			}
			/*Clear the conversion flag*/
			SET_BIT(ADCSRA,ADCSRA_ADIF);
		}
	}
	else
	{
		Local_u8ErrorState=BUSY_FUNC;
	}
	/*Return the reading*/
	return Local_u8ErrorState;

}

u8 ADC_u8StartConversionAsynch(u8 copy_u8Channel, u8* copy_pu8Reading, void(*copy_pvNotifactionFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if(ADC_u8BusyState==IDLE)
	{
		if((copy_u8Channel=NULL) || copy_pvNotifactionFunc==NULL)
		{
			Local_u8ErrorState=NULL_POINTER;
		}
		else
		{
			/*make ADC busy to work until idle*/
			ADC_u8BusyState= BUSY;

			/*make ISR source single channel Asynch*/
			ADC_u8ISRSorce=SINGLE_CHANNEL_ASYNCH;

			/*Initialize the reading variable globally */
			ADC_u8Reading=copy_pu8Reading;

			/*Initialize the callback notification function globally */
			ADC_pvCallBackNotifactionFunc=copy_pvNotifactionFunc;

			/*Clear MUX bits in ADMUX register*/
			ADMUX &= 0b11100000;

			/*Set the required channel into MUX bits*/
			ADMUX |= copy_u8Channel;

			/*Start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*ADC interrupt enable*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
	}
	else
	{
		Local_u8ErrorState=BUSY_FUNC;
	}
	return Local_u8ErrorState;
}

u8 ADC_u8mapping(f32 Copy_u8ADCReading, f32 Copy_u8TopScaleValue, f32 Copy_u8LowScaleValue)
{
	f32 Local_u8Output=0;

	Local_u8Output=(Copy_u8ADCReading/255)*(Copy_u8TopScaleValue-Copy_u8LowScaleValue)+Copy_u8LowScaleValue;

	return Local_u8Output;
}


u8 ADC_u8StartChainAsynch(Chain_t* Copy_Chain)
{
	u8 Local_u8ErrorState=OK;
	/*Check Null pointer*/
	if(Copy_Chain==NULL)
	{
		Local_u8ErrorState=NULL_POINTER;

	}
	else
	{
		/*Check ADC Busy state*/
		if(ADC_u8BusyState==IDLE)
		{
			/*Make ADC state busy*/
			ADC_u8BusyState=BUSY;

			/*make ISR source chain Asynch*/
			ADC_u8ISRSorce=CHAIN_ASYNCH;

			/*Initialize Chain channel array */
			ADC_puChainChannelArr=Copy_Chain-> Channel;

			/*Initialize Chain results array */
			ADC_pu16ChainResultArr=Copy_Chain-> Results;

			/*Initialize number of channels */
			ADC_u8ChainSize=Copy_Chain-> Size;

			/*Initialize notification function */
			ADC_pvCallBackNotifactionFunc=Copy_Chain->NotifactionFunc;

			/*Initialize current conversion index*/
			ADC_u8ChainConversionIndex=0;

			/*Set required channel (first channel)*/
			ADMUX &= 0b11100000;
			ADMUX |=ADC_puChainChannelArr[ADC_u8ChainConversionIndex];

			/*Start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*ADC interrupt enable*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			Local_u8ErrorState=BUSY;
		}
	}

	return Local_u8ErrorState;
}


void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{
	if(ADC_u8ISRSorce== SINGLE_CHANNEL_ASYNCH)
	{
	/*make ADC idle because it is finished*/
	ADC_u8BusyState=IDLE;

	/*Read ADC result*/
	*ADC_u8Reading=ADCH;

	/*Invoke the callback notification function*/
	ADC_pvCallBackNotifactionFunc();

	/*disable ADC conversion complete interrupt*/
	CLR_BIT(ADCSRA,ADCSRA_ADIE);
	}
	else if(ADC_u8ISRSorce==CHAIN_ASYNCH)
	{
		/*Read the current conversion*/
		ADC_pu16ChainResultArr[ADC_u8ChainConversionIndex]=ADCH;

		/*Increment chain index*/
		ADC_u8ChainConversionIndex++;

		if(ADC_u8ChainConversionIndex==ADC_u8ChainSize)
		{
			/*Chain is finished*/
			/*ADC state is IDLE */
			ADC_u8BusyState=IDLE;

			/*Invoke callback notification Function*/
			ADC_pvCallBackNotifactionFunc();

			/*Disable ADC conversion complete*/
			CLR_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{


			/*Chain is not finished*/
			/*SET new required channel*/
			ADMUX &= 0b11100000;
			ADMUX |=ADC_puChainChannelArr[ADC_u8ChainConversionIndex];

			/*Start new conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);


		}
	}
}


