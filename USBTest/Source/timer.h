#ifndef __TIMER_H__
#define __TIMER_H__

#include "main.h"

void timerInit(void);
void timerDelay1Us(void);
void timerDelayUs(uint32_t duration);
void timerDelay10Us(void);
void timerDelay100Us(void);
void timerDelayMs(uint32_t numMs);

#endif // __TIMER_H__