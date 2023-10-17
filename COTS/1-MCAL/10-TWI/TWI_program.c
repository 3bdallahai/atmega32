/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	MCAL				******************/
/******************		SWC:	TWI					******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TWI_config.h"
#include "TWI_register.h"
#include "TWI_interface.h"
#include "TWI_private.h"

void TWI_voidMasterINIT(u8 copy_u8Address)
{
	//Set Clock frequency to 400Kbps
	//Set TWBR to 2
	TWBR=2;

	//Clear the 2 bits of TWPS
	CLR_BIT(TWSR,TWSR_TWPS0);
	CLR_BIT(TWSR,TWSR_TWPS1);

	//Initialize the node address
	if (copy_u8Address !=0)
	{
		TWAR= copy_u8Address<<1;
	}
	//Enable TWI
	SET_BIT(TWCR,TWCR_TWEN);
}

void TWI_voidMSlaveINIT(u8 copy_u8Address)
{
	//Initialize the node address
	TWAR= copy_u8Address<<1;

	//Enable TWI
	SET_BIT(TWCR,TWCR_TWEN);
}

TWI_ERRStatus TWI_SendStartCondition(void)
{
	TWI_ERRStatus Local_ErrorStatus=NoError;

	//Send Start condition on the bus
	SET_BIT(TWCR,TWCR_TWSTA);

	//Clear the interrupt flag to start the operation
	SET_BIT(TWCR,TWCR_TWINT);

	//Wait until the interrupt flag is raised and the operation is finished
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	if ((TWSR & 0xF8) != START_ACK)
	{
		Local_ErrorStatus=StartConditionErr;
	}
	else
	{
		//do nothing
	}
	return Local_ErrorStatus;
}

TWI_ERRStatus TWI_SendReapetedStart(void)
{
	TWI_ERRStatus Local_ErrorStatus=NoError;

	//Send Start condition on the bus
	SET_BIT(TWCR,TWCR_TWSTA);

	//Clear the interrupt flag to start the operation
	SET_BIT(TWCR,TWCR_TWINT);

	//Wait until the interrupt flag is raised and the operation is finished
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	if ((TWSR & 0xF8) != REP_START_ACK)
	{
		Local_ErrorStatus=ReapetedStartErr;
	}
	else
	{
		//do nothing
	}
	return Local_ErrorStatus;
}

TWI_ERRStatus TWI_SendSlaveAddressWithWrite(u8 copy_u8SlaveAddress)
{
	TWI_ERRStatus Local_ErrorStatus=NoError;
	//clear the start condition bit
	CLR_BIT(TWCR,TWCR_TWSTA);
	//Set the slave address to the 7 MSBs in the data register
	TWDR=(copy_u8SlaveAddress<<1);
	CLR_BIT(TWDR,0);				//for write request
	//Clear the interrupt flag to start the operation
	SET_BIT(TWCR,TWCR_TWINT);

	//Wait until the interrupt flag is raised and the operation is finished
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	if ((TWSR & 0xF8) != SLAVE_ADD_AND_WR_ACK)
	{
		Local_ErrorStatus=SlaveAddressWithWriteErr;
	}
	else
	{
		//do nothing
	}


	return Local_ErrorStatus;
}

TWI_ERRStatus TWI_SendSlaveAddressWithRead(u8 copy_u8SlaveAddress)
{
	TWI_ERRStatus Local_ErrorStatus=NoError;
	//clear the start condition bit
	CLR_BIT(TWCR,TWCR_TWSTA);
	//Set the slave address to the 7 MSBs in the data register
	TWDR=(copy_u8SlaveAddress<<1);
	SET_BIT(TWDR,0);				//for write request
	//Clear the interrupt flag to start the operation
	SET_BIT(TWCR,TWCR_TWINT);

	//Wait until the interrupt flag is raised and the operation is finished
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	if ((TWSR & 0xF8) != SLAVE_ADD_AND_RD_ACK)
	{
		Local_ErrorStatus=SlaveAddressWithReadErr;
	}
	else
	{
		//do nothing
	}
	return Local_ErrorStatus;
}

TWI_ERRStatus TWI_MasterWriteDataByte(u8 copy_u8Data)
{
	TWI_ERRStatus Local_ErrorStatus=NoError;

	//write the data byte
	TWDR=copy_u8Data;
	//Clear the interrupt flag to start the operation
	SET_BIT(TWCR,TWCR_TWINT);

	//Wait until the interrupt flag is raised and the operation is finished
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	if ((TWSR & 0xF8) != MSTR_WR_BYTE_ACK)
	{
		Local_ErrorStatus=MasterWriteErr;
	}
	else
	{
		//do nothing
	}

	return Local_ErrorStatus;
}

TWI_ERRStatus TWI_MasterReadDataByte(u8* copy_pu8Data)
{
	TWI_ERRStatus Local_ErrorStatus=NoError;

	//Enable Master generating acknowledge bit after receiving the data
	SET_BIT(TWCR,TWCR_TWEA);
	//Clear the interrupt flag for the slave to send the data
	SET_BIT(TWCR,TWCR_TWINT);

	//Wait until the interrupt flag is raised and the operation is finished
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	if ((TWSR & 0xF8) != MSTR_RD_BYTE_ACK)
	{
		Local_ErrorStatus=MasterReadErr;
	}
	else
	{
		*copy_pu8Data=TWDR;
	}


	return Local_ErrorStatus;
}

void TWI_voidSendStopCondition(void)
{
	//generate stop condition on the bus
	SET_BIT(TWCR,TWCR_TWSTO);
	//Clear the interrupt flag to start the operation
	SET_BIT(TWCR,TWCR_TWINT);

}
