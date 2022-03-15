#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "app.h"

void protocolInit(void);
void protocolHandlePipeState(void);

#define iAP2_MAXIMUM_BULK_ENDPOINT_SIZE					         										64

#define IAP2_STATE_USB_START 												         							0
#define IAP2_STATE_USB_CONFIGURED 													         				1
#define IAP2_STATE_FREE																		         			10

#define iAP2_MAX_LOOP_DELAY 												         							200

void protocolSendControlData(uint8_t count);
void protoclSendNativeData(uint8_t *address, uint8_t count);

#endif //__PROTOCOL_H__
