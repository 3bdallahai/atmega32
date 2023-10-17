/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	MCAL				******************/
/******************		SWC:	SPI					******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/


#ifndef		SPI_REGISTER_H_
#define		SPI_REGISTER_H_

#define	SPCR	*((volatile u8*)0x2D)	//SPI Control Register
#define	SPCR_SPIE		7				//SPI Interrupt Enable
#define	SPCR_SPE		6				//SPI Enable
#define	SPCR_DORD		5				//Data order, 1for LSB first and 0 for MSB first
#define	SPCR_MSTR       4               //Master/Slave Select
#define	SPCR_CPOL       3               //Clock Polarity
#define	SPCR_CPHA       2               //Clock Phase
#define	SPCR_SPR1       1               //SPI Clock Rate Select 1 and 0
#define	SPCR_SPR0       0               


#define	SPSR	*((volatile u8*)0x2E)	//SPI Status Register
#define	SPSR_SPIF       7               //SPI Interrupt Flag
#define	SPSR_WCOL       6               //Write Collision flag
#define	SPSR_SPI2X      0               //Double SPI Speed bit

#define SPDR	*((volatile u8*)0x2F)	//SPI Data Register

#endif
