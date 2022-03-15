#ifndef __STM32L1xx_CONF_H__
#define __STM32L1xx_CONF_H__

#include "stm32l1xx_adc.h"
//#include "stm32l1xx_aes.h"
//#include "stm32l1xx_comp.h"
//#include "stm32l1xx_crc.h"
//#include "stm32l1xx_dac.h"
//#include "stm32l1xx_dbgmcu.h"
//#include "stm32l1xx_dma.h"
#include "stm32l1xx_exti.h"
//#include "stm32l1xx_flash.h"
//#include "stm32l1xx_fsmc.h"
#include "stm32l1xx_gpio.h"
//#include "stm32l1xx_i2c.h"
//#include "stm32l1xx_iwdg.h"
//#include "stm32l1xx_lcd.h"
//#include "stm32l1xx_opamp.h"
#include "stm32l1xx_pwr.h"
#include "stm32l1xx_rcc.h"
//#include "stm32l1xx_rtc.h"
//#include "stm32l1xx_sdio.h"
//#include "stm32l1xx_spi.h"
#include "stm32l1xx_syscfg.h"
//#include "stm32l1xx_tim.h"
//#include "stm32l1xx_usart.h"
//#include "stm32l1xx_wwdg.h"
#include "misc.h"  /* High level functions for NVIC and SysTick (add-on to CMSIS functions) */

// Uncomment the line below to expanse the "assert_param" macro in the Standard Peripheral Library drivers code
//#define USE_FULL_ASSERT    1

#ifdef  USE_FULL_ASSERT
   #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
   void assert_failed(uint8_t* file, uint32_t line);
#else
   #define assert_param(expr) ((void)0)
#endif

#endif // __STM32L1xx_CONF_H__