#ifndef __DRIVER_GPIO_H__
#define __DRIVER_GPIO_H__

#include "stm32f10x.h"
#include "Common_Delay.h"

#define SCK_H (GPIOB->ODR |= GPIO_ODR_ODR12)
#define SCK_L (GPIOB->ODR &= ~GPIO_ODR_ODR12)

#define OUT_READ (GPIOB->IDR & GPIO_IDR_IDR13)

void Driver_GPIO_Init(void);

void Driver_GPIO_WaiteKey3Pressed(void);

#endif

