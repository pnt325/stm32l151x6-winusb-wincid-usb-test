#ifndef __HW_CONFIG_H__
#define __HW_CONFIG_H__

#include "bsp.h"

void Set_System(void);
void Set_USBClock(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(void);
void USB_Cable_Config (FunctionalState NewState);

#endif // __HW_CONFIG_H__