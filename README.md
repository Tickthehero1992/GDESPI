Library SPI for GDE chips

This library describes Wire for working with GDE/Waveshares-displays.

GDESPI-wire structure, contains:
- pinInfoType MISO, portType MISO_PORT \n
- pinInfoType MOSI, portType MOSI_PORT \n
- pinInfoType SCK, portType SCK_PORT \n
- pinInfoType CSS, portType CSS_PORT \n
- pinInfoType DC, portType DC_PORT \n
- pinInfoType BS, portType BS_PORT \n
- uint32_t Speed

pinInfoType - describing type of pins (example: for stm32 uint32_t)\n
portType - describing type of ports (example: for stm32 HAL GPIO_TypeDef*)\n
GDESPI_GPIO_SET/RESET(_port,_pin) - set reset pinstate (example: for stm32 HAL HAL_GPIO_WRITE(_port,_pin,  GPIO_PIN_SET))\n
GDESPI_READ(_port, _pin) - read pinstate (example stm32 HAL HAL_GPIO_ReadPin(_port,_pin))



GDESPI_INIT(GDESPI) - wire initialization 
GDESPI_Delay_MS(uint16_t) - Delay 
GDESPI_Delay(GDESPI) - SPI delay

GDESPI_WRITE(GDESPI, uint8_t) - write Byte
GDESPI_READ(GDESPI)-read Byte
GDESPI_FULL_DPLX(GDESPI,uint8_t) - read/write BYTE

GDESPI_WRITE_CMD(GDESPI,uint8_t) - write display command
GDESPI_WRITE_DATA(GDESPI,uint8_t) - write display data

