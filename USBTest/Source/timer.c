#include "timer.h"
#include "stm32l1xx_tim.h"

void timerInit(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	// Setup SysTick interrupt
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	NVIC_InitStructure.NVIC_IRQChannel = SysTick_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}


#pragma optimize=none
void timerDelay1Us(void)
{
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
}

#pragma optimize=none
void timerDelay10Us(void)
{
	timerDelay1Us();
	timerDelay1Us();
	timerDelay1Us();
	timerDelay1Us();
	timerDelay1Us();
	timerDelay1Us();
	timerDelay1Us();
	timerDelay1Us();
	timerDelay1Us();
	timerDelay1Us();
}

#pragma optimize=none
void timerDelay100Us(void)
{
	timerDelay10Us();
	timerDelay10Us();
	timerDelay10Us();
	timerDelay10Us();
	timerDelay10Us();
	timerDelay10Us();
	timerDelay10Us();
	timerDelay10Us();
	timerDelay10Us();
	timerDelay10Us();
}

#pragma optimize=none
void timerDelayUs(uint32_t duration)
{
	while (duration)
	{
		timerDelay1Us();
		duration--;
	}
}

#pragma optimize=none
void timerDelayMs(uint32_t numMs)
{
	uint32_t i;

	for (i=0;i<numMs;i++)
	{
		timerDelay100Us();
		timerDelay100Us();
		timerDelay100Us();
		timerDelay100Us();
		timerDelay100Us();
		timerDelay100Us();
		timerDelay100Us();
		timerDelay100Us();
		timerDelay100Us();
		timerDelay100Us();
	}
}