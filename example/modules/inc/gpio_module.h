/*
 * gpio_module.h
 *
 *  Created on: May 31, 2023
 *      Author: renatobarresi
 */

#pragma once
#ifndef __cpluscplus

#include "stm32f4xx_hal.h"

void initGPIOOutput(uint16_t pin, GPIO_TypeDef *port);

#endif /* INC_GPIO_MODULE_H_ */
