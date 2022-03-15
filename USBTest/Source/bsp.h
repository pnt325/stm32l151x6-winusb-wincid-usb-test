#ifndef __BSP_H__
#define __BSP_H__

#include "stm32l1xx.h"

// LED
#define LED_PIN											GPIO_Pin_14
#define LED_PORT											GPIOC
#define LED_PORT_PERIPH									RCC_AHBPeriph_GPIOC
#define LED_OFF											(LED_PORT->BSRRH = LED_PIN)
#define LED_ON 											(LED_PORT->BSRRL = LED_PIN)

// Unique device ID registers
#define U_ID1												(0x1FF80050)
#define U_ID2												(0x1FF80054)
#define U_ID3												(0x1FF80064)

#endif // __BSP_H__