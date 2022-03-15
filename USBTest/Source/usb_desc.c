#include "usb_lib.h"
#include "usb_desc.h"
#include <string.h>
#include "app.h"

#define CLASS           0xFFu
#define SUBCLASS        0x00u

// USB Standard Device Descriptor
const uint8_t USBiAP2_DeviceDescriptor[] =
{
	0x12u,											// bLength
	USB_DEVICE_DESCRIPTOR_TYPE,				// bDescriptorType
	0x00u, 0x02u,									// bcdUSB = 2.00
	CLASS,											// bDeviceClass
	SUBCLASS,										// bDeviceSubClass
	0x00u,											// bDeviceProtocol
	0x40u,											// bMaxPacketSize0
   0xAEu, 0x26u,									// idVendor = Oscium/Dechnia
	PRODUCT, 0x00u,								// idProduct = WiPry 6E
	CANDIDATE, VERSION,							// bcdDevice
	0x02u,											// Manufacturer string index
	0x03u,											// Product string index
	0x06u,											// Serial string index
	0x01u												// bNumConfigurations
};

const uint8_t USBiAP2_ConfigDescriptor[] =
{
	0x09u,											// Config Descriptor Length
	USB_CONFIGURATION_DESCRIPTOR_TYPE,		// DescriptorType: CONFIG
	0x40u, 0x00u,									// wTotalLength
	0x02u,											// bNumInterfaces
	0x01u,											// bConfigurationValue
	0x00u,											// iConfiguration (index of configuration)
	0x80u,											// bmAttributes (bus powered)
	0x32u,											// bMaxPower (100mA)

      // Interface Descriptor
      0x09u,											// Interface Descriptor Length
      USB_INTERFACE_DESCRIPTOR_TYPE,			// DescriptorType: INTERFACE
      0x00u,											// bInterfaceNumber
      0x00u,											// bAlternateSetting
      0x02u,											// bNumEndpoints
      CLASS,											// bInterfaceClass
      SUBCLASS,										// bInterfaceSubClass
      0x00u,											// bInterfaceProtocol
      0x01u,											// iInterface

         // Endpoint Descriptor (EP1 - OUT)
         0x07u,											// Endpoint Descriptor Length
         USB_ENDPOINT_DESCRIPTOR_TYPE,				// DescriptorType: ENDPOINT
         0x01u,											// bEndpointAddress
         0x02u,											// bmAttributes
         0x40u, 0x00u,									// wMaxPacketSize
         0x01u,											// bInterval

         // Endpoint Descriptor (EP2 - IN)
         0x07u,											// Endpoint Descriptor Length
         USB_ENDPOINT_DESCRIPTOR_TYPE,				// DescriptorType: ENDPOINT
         0x82u,											// bEndpointAddress
         0x02u,											// bmAttributes
         0x40u, 0x00u,									// wMaxPacketSize
         0x01u,											// bInterval

      // Interface Descriptor
      0x09u,											// Interface Descriptor Length
      USB_INTERFACE_DESCRIPTOR_TYPE,			// DescriptorType: INTERFACE
      0x01u,											// bInterfaceNumber
      0x00u,											// bAlternateSetting
      0x00u,											// bNumEndpoints
      CLASS,											// bInterfaceClass            
      SUBCLASS,										// bInterfaceSubClass
      0x00u,											// bInterfaceProtocol
      0x05u,											// iInterface

      // Interface Descriptor
      0x09u,											// Interface Descriptor Length
      USB_INTERFACE_DESCRIPTOR_TYPE,			// DescriptorType: INTERFACE
      0x01u,											// bInterfaceNumber
      0x01u,											// bAlternateSetting
      0x02u,											// bNumEndpoints
      CLASS,											// bInterfaceClass             
      SUBCLASS,										// bInterfaceSubClass
      0x00u,											// bInterfaceProtocol
      0x05u,											// iInterface

         //	Endpoint Descriptor (EP3 - OUT)
         0x07u,											// Endpoint Descriptor Length
         USB_ENDPOINT_DESCRIPTOR_TYPE,				// DescriptorType: ENDPOINT
         0x03u,											// bEndpointAddress
         0x02u,											// bmAttributes
         0x40u, 0x00u,									// wMaxPacketSize
         0x01u,											// bInterval

         // Endpoint Descriptor (EP4 - IN)
         0x07u,											// Endpoint Descriptor Length
         USB_ENDPOINT_DESCRIPTOR_TYPE,				// DescriptorType: ENDPOINT
         0x84u,											// bEndpointAddress
         0x02u,											// bmAttributes
         0x40u, 0x00u,									// wMaxPacketSize
         0x01u,											// bInterval
};


// USB String Descriptors
uint8_t USBiAP2_StringLangID[USBiAP2_SIZE_STRING_MAX_SIZE];
uint8_t USBiAP2_StringVendor[USBiAP2_SIZE_STRING_MAX_SIZE];
uint8_t USBiAP2_StringProduct[USBiAP2_SIZE_STRING_MAX_SIZE];
uint8_t USAiAP2_StringInterface[USBiAP2_SIZE_STRING_MAX_SIZE];
uint8_t USBiAP2_StringProtocol[USBiAP2_SIZE_STRING_MAX_SIZE];
uint8_t USBiAP2_StringSerial[USBiAP2_SIZE_STRING_MAX_SIZE];

void createDescriptor(uint8_t* packet, uint8_t maxLength, char * descriptor, bool addZero );

void createDescriptor(uint8_t* packet, uint8_t maxLength, char * descriptor, bool addZero ) 
{
   size_t descLength;
   uint16_t length;
   
   if (packet == NULL || maxLength < 2 || descriptor == NULL) return;
  
   descLength = strlen(descriptor);
  
   length = descLength * (addZero ? 2 : 1);
   if (length + 2 > maxLength) return;
  
   packet[0] = length+2;
   packet[1] = USB_STRING_DESCRIPTOR_TYPE;
  
   if (addZero)
   {
      for (int i = 0; i < descLength; i++) 
      {
         packet[2 + 2*i ] = descriptor[i];
         packet[2 + 2*i + 1] = 0;
      }
   } else {
      memcpy(&packet[2], descriptor, length);
   }
}

void USBiAP2_ProcessDescriptors(void)
{
   uint8_t siliconID[17];
   uint32_t id;

   createDescriptor(USBiAP2_StringLangID, USBiAP2_SIZE_STRING_MAX_SIZE, "\x09\x04", FALSE);
   createDescriptor(USBiAP2_StringProduct, USBiAP2_SIZE_STRING_MAX_SIZE, "USBTest", TRUE);
   createDescriptor(USBiAP2_StringVendor, USBiAP2_SIZE_STRING_MAX_SIZE, "Oscium", TRUE);
   createDescriptor(USAiAP2_StringInterface, USBiAP2_SIZE_STRING_MAX_SIZE, "USBTest Interface", TRUE);
   createDescriptor(USBiAP2_StringProtocol, USBiAP2_SIZE_STRING_MAX_SIZE, "com.oscium.USBTest", TRUE);
    
   id = *(uint32_t *)U_ID1;
  
   siliconID[0] = '1';
   siliconID[1] = '3';
   siliconID[2] = '3';
   siliconID[3] = '7';
   memcpy( (void *)&siliconID[4], (void *)&id, 4 );
   id = *(uint32_t *)U_ID2;
   memcpy( (void *)&siliconID[8], (void *)&id, 4 );
   id = *(uint32_t *)U_ID3;
   memcpy( (void *)&siliconID[12], (void *)&id, 4 );
  
   for (int i=0; i<16; i++) 
   {
      if (siliconID[i]<32 || siliconID[i] >126) siliconID[i] = '0';
   }
   siliconID[16] = '\0';
  
   createDescriptor(USBiAP2_StringSerial, USBiAP2_SIZE_STRING_MAX_SIZE, (char*)siliconID, TRUE);
}
   