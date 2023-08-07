/*
 * SPI_Functions.h
 *
 *  Created on: Aug 2, 2023
 *      Author: AnastasII
 */

#include "stm32f103xb.h"
#include "main.h"

#ifndef SPI_FUNCTIONS_H_
#define SPI_FUNCTIONS_H_

typedef enum
{
  OK       = 0x00U,
  ERR      = 0x01U,
  BUSY     = 0x02U,
  TIMEOUT  = 0x03U
}SPI_STATUS;

void SPI_init(void);
SPI_STATUS SPI_Transmit(SPI_TypeDef* SPI, uint8_t* data, uint16_t size, uint32_t time);

#endif /* SPI_FUNCTIONS_H_ */
