#include "nrf24_low.h"
#include "arduino.h"
#include "SPI.h"


#define ce_pin 9
#define csn_pin 10
#define low 0
#define high 1

void nRF24L01_HW_Init(void){
	
	pinMode(ce_pin,OUTPUT);
	pinMode(csn_pin,OUTPUT);
	ce(LOW);
	csn(HIGH);

	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE0);
	SPI.setClockDivider(SPI_CLOCK_DIV8);
	SPI.begin();
}
void nRF24L01_Delay_us(unsigned long n){
	delayMicroseconds(n);
}
void nRF24L01_CE(uint8_t level){
	digitalWrite(ce_pin,level);
}
void nRF24L01_NSS(uint8_t level){
	digitalWrite(csn_pin,level);
}
uint8_t nRF24L01_Read_Regs(uint8_t reg, uint8_t *buf, uint8_t len){
	uint8_t status;

  	nRF24L01_NSS(LOW);
  	status = nRF24L01_SPI_Send_Byte( R_REGISTER | ( REGISTER_MASK & reg ) );
  	while ( len-- )
    	*buf++ = nRF24L01_SPI_Send_Byte(0xff);
  	nRF24L01_NSS(HIGH);
  	
	return status;	
}
uint8_t nRF24L01_Write_Regs(uint8_t reg, uint8_t *buf, uint8_t len){
	uint8_t status;

	nRF24L01_NSS(LOW);
	status = nRF24L01_SPI_Send_Byte( W_REGISTER | ( REGISTER_MASK & reg ) );
	while ( len-- )
		nRF24L01_SPI_Send_Byte(*buf++);
	nRF24L01_NSS(HIGH);

	return status;
}
uint8_t nRF24L01_SPI_Send_Byte(uint8_t data){
	return SPI.transfer(data);
}
