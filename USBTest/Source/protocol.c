#include "protocol.h"
#include "timer.h"
#include "gpio.h"
#include "bsp.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "usb_mem.h"
#include "usb_desc.h"
#include "app.h"
#include <string.h>
#include <stdio.h>

// usb defines
volatile uint8_t ep1DataReady = 0;
volatile uint8_t ep1DataLength = 0;
volatile uint8_t ep2DataSent = 0;
volatile uint8_t ep3DataReady = 0;
volatile uint8_t ep3DataLength = 0;
volatile uint8_t ep4DataSent = 0;
volatile uint8_t iAP2BulkInEndpoint[iAP2_MAXIMUM_BULK_ENDPOINT_SIZE];

uint8_t packetTemp[255];

// local iAP2 defines
static volatile uint8_t state = IAP2_STATE_USB_START;
static uint8_t iAP2_SerialNumber[17];

uint8_t USBiAP_configChanged=0;
uint8_t USBiAP_eaAltSetting=0;

extern volatile uint8_t iAP2BulkOutEndpoint[iAP2_MAXIMUM_BULK_ENDPOINT_SIZE];

void protocolInit(void)
{
	uint8_t i;
	uint32_t id1 = *(uint32_t *)U_ID1;
	uint32_t id2 = *(uint32_t *)U_ID2;
	uint32_t id3 = *(uint32_t *)U_ID3;

   USBiAP2_ProcessDescriptors();

	for(i=0;i<17;i++) iAP2_SerialNumber[i] = 0;

   iAP2_SerialNumber[0] = '0';
   iAP2_SerialNumber[1] = '0';
   iAP2_SerialNumber[2] = '0';
   iAP2_SerialNumber[3] = '0';
   memcpy( (void *)&iAP2_SerialNumber[4], (void *)&id1, 4 );
	memcpy( (void *)&iAP2_SerialNumber[8], (void *)&id2, 4 );
	memcpy( (void *)&iAP2_SerialNumber[12], (void *)&id3, 4 );

	for (i=0;i<16;i++)
	{
      if (iAP2_SerialNumber[i] < 32 || iAP2_SerialNumber[i] > 126) iAP2_SerialNumber[i] = '0';
	}
	iAP2_SerialNumber[16] = '\0';
}

void protocolHandlePipeState(void)
{
   uint8_t loopCount;
  
	switch (state)
	{
		case IAP2_STATE_USB_START:
		Set_System();
		Set_USBClock();
		USB_Interrupts_Config();
		USB_Init();

		timerDelayMs(200);

		while (bDeviceState != CONFIGURED)
		{
			if (loopCount == iAP2_MAX_LOOP_DELAY)
			{
				break;
			}
			timerDelayMs(10);
			loopCount++;
		}
		state = IAP2_STATE_USB_CONFIGURED;
		break;

		case IAP2_STATE_USB_CONFIGURED:
      state = IAP2_STATE_FREE;
      break;
      
		case IAP2_STATE_FREE:
		if (USBiAP_configChanged)
		{
			if(USBiAP_eaAltSetting == 1) LED_ON;
			else LED_OFF;
			USBiAP_configChanged = 0;
		}

		// Check for ACK packet (and respond with no payload)
		if (ep1DataReady) ep1DataReady = 0;
		break;

		default:
	  	break;
   }
}

void protocolSendControlData(uint8_t count)
{
	UserToPMABufferCopy((uint8_t *)iAP2BulkInEndpoint, ENDP2_TXADDR, count);
	SetEPTxCount(ENDP2, count);
	SetEPTxValid(ENDP2);
}

void protoclSendNativeData(uint8_t *address, uint8_t count)
{
	UserToPMABufferCopy((uint8_t *)address, ENDP4_TXADDR, count);
	SetEPTxCount(ENDP4, count);
	SetEPTxValid(ENDP4);
}