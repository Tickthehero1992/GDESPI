#ifndef __GDESPI_H
#define __GDESPI_H

#include "main.h"

#define portType GPIO_TypeDef*
#define pinInfoTypeMCU uint32_t

typedef struct GDESPI
{
	pinInfoTypeMCU MISO;
	portType MISO_PORT;

	pinInfoTypeMCU MOSI;
	portType MOSI_PORT;

	pinInfoTypeMCU SCK;
	portType SCK_PORT;


	pinInfoTypeMCU CSS;
	portType CSS_PORT;

	pinInfoTypeMCU DC;
	portType DC_PORT;

	pinInfoTypeMCU RST;
	portType RST_PORT;

	pinInfoTypeMCU BS;
	portType BS_PORT;

	uint32_t SPEED;
}GDESPI;



#define GDESPI_GPIO_SET(_port, _pin)  HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_SET)
#define GDESPI_GPIO_RESET(_port, _pin) HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_RESET)
#define GDESPI_GPIO_READ(_port,_pin) HAL_GPIO_ReadPin(_port,_pin)

void GDESPI_INIT(GDESPI);
void GDESPI_Delay_MS(uint16_t);

void GDESPI_delay(GDESPI);
void GDESPI_WRITE(GDESPI,uint8_t);
uint8_t GDESPI_READ(GDESPI);
uint8_t GDESPI_FULL_DPLX(GDESPI,uint8_t);

void GDESPI_WRITE_CMD(GDESPI,uint8_t);
void GDESPI_WRITE_DATA(GDESPI, uint8_t);

//uint8_t GDESPI_READ(GDESPI);


#endif
