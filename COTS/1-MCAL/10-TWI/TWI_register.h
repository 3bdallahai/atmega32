/*********************************************************************/
/*********************************************************************/
/******************		Author: Abdallah Ashraf		******************/
/******************		Layer:	MCAL				******************/
/******************		SWC:	TWI					******************/
/******************		Version:1.00				******************/
/*********************************************************************/
/*********************************************************************/


#ifndef		TWI_REGISTER_H_
#define		TWI_REGISTER_H_

// TWI Bit Rate Register
#define	TWBR	*((volatile u8*)0x20)	//TWBR selects the division factor for the bit rate generator

//TWI Control Register
#define	TWCR	*((volatile u8*)0x56)
#define	TWCR_TWINT		7				//TWI Interrupt Flag	
#define	TWCR_TWEA       6               //TWI Enable Acknowledge Bit, write 0 to disconnecte the device from TWI serial bus
#define	TWCR_TWSTA      5               //TWI START Condition Bit,Generate Start condition 	
#define	TWCR_TWSTO      4               //TWI STOP Condition Bit,Generate Stop condition
#define	TWCR_TWWC       3               //TWI Write Collision Flag
#define	TWCR_TWEN       2               //TWI Enable
#define	TWCR_TWIE       0               //TWI Interrupt Enable

//TWI Status Register
#define	TWSR	*((volatile u8*)0x21)
#define	TWSR_TWPS1		1				//TWI Prescaler Bits
#define	TWSR_TWPS0		0				

//TWI Data Register
#define TWDR	*((volatile u8*)0x23)

//TWI (Slave) Address Register
#define TWAR	*((volatile u8*)0x22)
#define TWAR_TWGCE		0				//TWI General Call Recognition Enable Bit



#endif