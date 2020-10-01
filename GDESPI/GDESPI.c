#include "GDESPI.h"



#define INITPIN(_pin,_port, _mode) {GPIO_InitTypeDef GPIO_InitStructure; \
	  GPIO_InitStructure.Pin = _pin; \
	  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; \
	  GPIO_InitStructure.Mode = _mode; \
	  HAL_GPIO_Init(_port, &GPIO_InitStructure); }

void GDESPI_INIT(GDESPI SPI)
{

	INITPIN(SPI.RST, SPI.RST_PORT, GPIO_MODE_OUTPUT_PP);
	INITPIN(SPI.CSS, SPI.CSS_PORT, GPIO_MODE_OUTPUT_PP);
	INITPIN(SPI.MOSI, SPI.MOSI_PORT, GPIO_MODE_OUTPUT_PP);
	INITPIN(SPI.SCK, SPI.SCK_PORT, GPIO_MODE_OUTPUT_PP);
	INITPIN(SPI.DC, SPI.DC_PORT, GPIO_MODE_OUTPUT_PP);

	INITPIN(SPI.BS, SPI.BS_PORT, GPIO_MODE_INPUT);
	INITPIN(SPI.MISO, SPI.MISO_PORT, GPIO_MODE_INPUT);


}


void GDESPI_Delay_MS(uint16_t MS)
{
    for(uint16_t j=0;j<MS;j++)
	{
        for(uint16_t i=0; i<256; i++);
    }
};

void GDESPI_delay(GDESPI SPI)
{
  uint32_t i=0;
  uint32_t TIME=SPI.SPEED;
  while(TIME)
  {
	  for(i=0; i<SPI.SPEED; i++)
		  TIME--;
  }

}


void GDESPI_WRITE(GDESPI SPI,uint8_t DATA)
{
   GDESPI_delay(SPI);
   GDESPI_GPIO_RESET(SPI.CSS_PORT, SPI.CSS);
   for(uint8_t i=0; i<8; i++)
   {
	   GDESPI_GPIO_RESET(SPI.SCK_PORT,SPI.SCK);
	   GDESPI_delay(SPI);
	   if(DATA&0X80) GDESPI_GPIO_SET(SPI.MOSI_PORT,SPI.MOSI);
	   else GDESPI_GPIO_RESET(SPI.MOSI_PORT,SPI.MOSI);
	   DATA = DATA<<1;
	   GDESPI_delay(SPI);
	   GDESPI_GPIO_SET(SPI.SCK_PORT,SPI.SCK);
	   GDESPI_delay(SPI);
   }
   GDESPI_GPIO_SET(SPI.CSS_PORT, SPI.CSS);
}


uint8_t GDESPI_READ(GDESPI SPI)
{
	uint8_t output;
	GDESPI_GPIO_RESET(SPI.CSS_PORT, SPI.CSS);
	GDESPI_delay(SPI);
	   for(uint8_t i=0; i<8; i++)
	   {
		   GDESPI_GPIO_RESET(SPI.SCK_PORT,SPI.SCK);
		   GDESPI_delay(SPI);
		   if(GPIOD_READ_PIN(SPI.MISO_PORT, SPI.MISO)) output|=1;
		   output=output<<1;
		   GDESPI_GPIO_SET(SPI.SCK_PORT,SPI.SCK);
		   GDESPI_delay(SPI);
	   }
	   GDESPI_GPIO_SET(SPI.CSS_PORT, SPI.CSS);
	   return output;
}



uint8_t GDESPI_FULL_DPLX(GDESPI SPI,uint8_t DATA)
{
	uint8_t output;
	GDESPI_GPIO_RESET(SPI.CSS_PORT, SPI.CSS);
	GDESPI_delay(SPI);
	for(uint8_t i=0; i<8; i++)
	{
		 GDESPI_GPIO_RESET(SPI.SCK_PORT,SPI.SCK);
		 GDESPI_delay(SPI);
		 if(GPIOD_READ_PIN(SPI.MISO_PORT, SPI.MISO)) output|=1;
		 output=output<<1;
		 if(DATA&0X80) GDESPI_GPIO_SET(SPI.MOSI_PORT,SPI.MOSI);
	     else GDESPI_GPIO_RESET(SPI.MOSI_PORT,SPI.MOSI);
	     DATA = DATA<<1;
	     GDESPI_GPIO_SET(SPI.SCK_PORT,SPI.SCK);
	     GDESPI_delay(SPI);
	}
	GDESPI_GPIO_SET(SPI.CSS_PORT, SPI.CSS);
    return output;
}

void GDESPI_WRITE_CMD(GDESPI SPI,uint8_t CMD)
{
	GDESPI_delay(SPI);
	GDESPI_GPIO_RESET(SPI.DC_PORT, SPI.DC);
	GDESPI_WRITE(SPI,CMD);
}

void GDESPI_WRITE_DATA(GDESPI SPI,uint8_t DATA)
{
	GDESPI_delay(SPI);
	GDESPI_GPIO_SET(SPI.DC_PORT, SPI.DC);
	GDESPI_WRITE(SPI,DATA);
}
