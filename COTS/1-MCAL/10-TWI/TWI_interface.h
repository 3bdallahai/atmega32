/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	MCAL				******************/
/******************		SWC:	TWI					******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/


#ifndef		TWI_INTERFACE_H_
#define		TWI_INTERFACE_H_

typedef enum {
		NoError,
		StartConditionErr,
		ReapetedStartErr,
		SlaveAddressWithWriteErr,
		SlaveAddressWithReadErr,
		MasterWriteErr,
		MasterReadErr,

}TWI_ERRStatus;

//Pass 0 in address argument if master will not be addressed
void TWI_voidMasterINIT(u8 copy_u8Address);

void TWI_voidMSlaveINIT(u8 copy_u8Address);

TWI_ERRStatus TWI_SendStartCondition(void);

TWI_ERRStatus TWI_SendReapetedStart(void);

TWI_ERRStatus TWI_SendSlaveAddressWithWrite(u8 copy_u8SlaveAddress);

TWI_ERRStatus TWI_SendSlaveAddressWithRead(u8 copy_u8SlaveAddress);

TWI_ERRStatus TWI_MasterWriteDataByte(u8 copy_u8Data);

TWI_ERRStatus TWI_MasterReadDataByte(u8* copy_pu8Data);

void TWI_voidSendStopCondition(void);

#endif
