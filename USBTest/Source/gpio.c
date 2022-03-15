#include "gpio.h"
#include "bsp.h"
#include "timer.h"
#include "STM32l1xx_gpio.h"
#include "STM32l1xx_tim.h"
#include "STM32l1xx_usart.h"

void gpioInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	// LED
	{
		// Enable the GPIO clock for port C
		RCC_AHBPeriphClockCmd(LED_PORT_PERIPH, ENABLE);

		// Configure the GPIO_LED pin
		GPIO_InitStructure.GPIO_Pin = LED_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
		GPIO_Init(LED_PORT, &GPIO_InitStructure);

		LED_OFF;
	}
}