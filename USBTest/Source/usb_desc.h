#ifndef __USB_DESC_H__
#define __USB_DESC_H__

#include <stdint.h>

#define USB_DEVICE_DESCRIPTOR_TYPE			0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE	0x02
#define USB_STRING_DESCRIPTOR_TYPE			0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE		0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE		0x05

#define USBiAP2_DEVICE_DESC					18
#define USBiAP2_SIZE_CONFIG_DESC			64		// was 64

#define USBiAP2_SIZE_STRING_LANGID      	4
#define USBiAP2_SIZE_STRING_VENDOR      	14
#define USBiAP2_SIZE_STRING_PRODUCT			16
#define USBiAP2_SIZE_STRING_INTERFACE		28
#define USBiAP2_SIZE_STRING_PROTOCOL		46
#define USBiAP2_SIZE_STRING_SERIAL			12		// 34 to use ID
#define USBiAP2_SIZE_STRING_WINUSB			18      //0x12
#define	USB_REQ_GET_OS_FEATURE_DESCRIPTOR	0x21

#define USBiAP2_EP1_RX_DATA_SIZE			64
#define USBiAP2_EP1_TX_DATA_SIZE			64
#define USBiAP2_EP2_RX_DATA_SIZE			64
#define USBiAP2_EP2_TX_DATA_SIZE			64
#define USBiAP2_EP3_RX_DATA_SIZE			64
#define USBiAP2_EP4_TX_DATA_SIZE			64
#define USBiAP2_EP7_TX_DATA_SIZE			64
#define USBiAP2_EP8_RX_DATA_SIZE			64

#define USBiAP2_SIZE_STRING_MAX_SIZE        64

#define USBiAP2_WINUSB_EXT_PROP_DESC_SIZE   142

#define  USBD_IDX_LANGID_STR                0x00U
#define  USBD_IDX_MFC_STR                   0x01U
#define  USBD_IDX_PRODUCT_STR               0x02U
#define  USBD_IDX_SERIAL_STR                0x03U
#define  USBD_IDX_CONFIG_STR                0x04U
#define  USBD_IDX_INTERFACE_STR             0x05U
#define  USBD_IDX_WINUSB_STR                0x06U

typedef struct
{
    // Header
    uint32_t dwLength;
    uint16_t bcdVersion;
    uint16_t wIndex;
    uint8_t bCount;
    uint8_t bReserved1[7];
    // Function Section 1
    uint8_t bFirstInterfaceNumber;
    uint8_t bReserved2;
    uint8_t bCompatibleID[8];
    uint8_t bSubCompatibleID[8];
    uint8_t bReserved3[6];
} USBD_CompatIDDescStruct;

// Exported functions
extern uint8_t USBiAP2_DeviceDescriptor[USBiAP2_DEVICE_DESC];
extern uint8_t USBiAP2_ConfigDescriptor[USBiAP2_SIZE_CONFIG_DESC];
extern uint8_t USBiAP2_StringLangID[USBiAP2_SIZE_STRING_MAX_SIZE];
extern uint8_t USBiAP2_StringVendor[USBiAP2_SIZE_STRING_MAX_SIZE];
extern uint8_t USBiAP2_StringProduct[USBiAP2_SIZE_STRING_MAX_SIZE];
extern uint8_t USAiAP2_StringInterface[USBiAP2_SIZE_STRING_MAX_SIZE];
extern uint8_t USBiAP2_StringProtocol[USBiAP2_SIZE_STRING_MAX_SIZE];
extern uint8_t USBiAP2_StringSerial[USBiAP2_SIZE_STRING_MAX_SIZE];
extern uint8_t USBD_StringWinUSB[USBiAP2_SIZE_STRING_WINUSB];
extern uint8_t USBD_ExtPropertiesDesc[USBiAP2_WINUSB_EXT_PROP_DESC_SIZE];
extern USBD_CompatIDDescStruct USBD_CompatIDDesc;

extern void USBiAP2_ProcessDescriptors(void);
#endif /* __USB_DESC_H__ */
