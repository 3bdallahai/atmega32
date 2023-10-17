/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	MCAL				******************/
/******************		SWC:	SPI					******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SPI_register.h"
#include "SPI_config.h"
#include "SPI_private.h"
#include "SPI_interface.h"

void SPI_voidSlaveINIT(void)
{
	//the LSB of the data word is transmitted first
	SET_BIT(SPCR,SPCR_DORD);
	//Clear MSTR to choose Slave
	CLR_BIT(SPCR,SPCR_MSTR);
	//Clear CPOL for Leading Edge: Rising and Trailing Edge:Falling
	CLR_BIT(SPCR,SPCR_CPOL);
	//Clear CPHA for Leading Edge: Sample and Trailing Edge:setup
	CLR_BIT(SPCR,SPCR_CPHA);
	//SPI Enable
	SET_BIT(SPCR,SPCR_SPE);
}


void SPI_voidMasterINIT(void)
{
	//the LSB of the data word is transmitted first
	SET_BIT(SPCR,SPCR_DORD);
	//SET MSTR to choose Master
	SET_BIT(SPCR,SPCR_MSTR);
	//Clear CPOL for Leading Edge: Rising and Trailing Edge:Falling
	CLR_BIT(SPCR,SPCR_CPOL);
	//Clear CPHA for Leading Edge: Sample and Trailing Edge:setup
	CLR_BIT(SPCR,SPCR_CPHA);
	//Set SCK frequency to divide by 8
	SET_BIT(SPCR,SPCR_SPR0);
	CLR_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPSR,SPSR_SPI2X);
	//SPI Enable
	SET_BIT(SPCR,SPCR_SPE);
}



u8 SPI_u8TranceiveData(u8 copy_u8Data)
{
	//send data to SPI data register
	SPDR=copy_u8Data;
	//wait until the transmission is finished
	while(GET_BIT(SPSR,SPSR_SPIF)==0);
	//read the data from the SPI data register
		return SPDR;

}
