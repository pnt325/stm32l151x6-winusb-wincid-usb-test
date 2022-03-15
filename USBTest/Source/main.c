#include "app.h"
#include "main.h"
#include "gpio.h"
#include "protocol.h"
#include "structs.h"

volatile IOS2DEV ios2dev;

void main(void)
{
	gpioInit();
	protocolInit();
 
	while (1)
	{
		protocolHandlePipeState();
	}
}