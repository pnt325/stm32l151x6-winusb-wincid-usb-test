#include "usb_lib.h"
#include "usb_istr.h"
#include "protocol.h"
#include "structs.h"

extern volatile uint8_t iAP2BulkOutEndpoint[iAP2_MAXIMUM_BULK_ENDPOINT_SIZE];
extern volatile IOS2DEV ios2dev;

extern volatile uint8_t ep1DataReady;
extern volatile uint8_t ep1DataLength;
extern volatile uint8_t ep2DataSent;

extern volatile uint8_t ep3DataReady;
extern volatile uint8_t ep3DataLength;
extern volatile uint8_t ep4DataSent;

// Function Name  : EP1_OUT_Callback
// Description    :
// Input          : None.
// Output         : None.
// Return         : None.
void EP1_OUT_Callback(void)
{
  ep1DataReady++;
  ep1DataLength = GetEPRxCount(ENDP1);
  PMAToUserBufferCopy((uint8_t *)iAP2BulkOutEndpoint, ENDP1_RXADDR, ep1DataLength);
  SetEPRxStatus(ENDP1, EP_RX_VALID);
}

// Function Name  : EP2_IN_Callback
// Description    :
// Input          : None.
// Output         : None.
// Return         : None.
void EP2_IN_Callback (void)
{
  ep2DataSent++;
}

// Function Name  : EP3_OUT_Callback
// Description    :
// Input          : None.
// Output         : None.
// Return         : None.
void EP3_OUT_Callback(void)
{
   static uint8_t *ptr = NULL;
   
   if (ptr == NULL) ptr = (uint8_t *)&ios2dev;
   
   ep3DataLength = GetEPRxCount(ENDP3);
   PMAToUserBufferCopy((uint8_t *)ptr, ENDP3_RXADDR, ep3DataLength);
   ep3DataReady++;
   
   if (ep3DataLength < 64)
   {
      ptr = (uint8_t *)&ios2dev;
   } 
   else
   {
      ptr += 64;
      if (ptr > (uint8_t *)&ios2dev + sizeof(ios2dev)) ptr = (uint8_t *)&ios2dev;                     // handle overflow case
   }
   
   SetEPRxStatus(ENDP3, EP_RX_VALID);
}

// Function Name  : EP4_IN_Callback
// Description    :
// Input          : None.
// Output         : None.
// Return         : None.
void EP4_IN_Callback (void)
{
  ep4DataSent++;
}
