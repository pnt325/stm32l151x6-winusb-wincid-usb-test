/**
  ******************************************************************************
  * @file    usb_prop.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   All processing related to Virtual Com Port Demo
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "hw_config.h"

uint8_t Request = 0;

extern uint8_t USBiAP_configChanged;
extern uint8_t USBiAP_eaAltSetting;

DEVICE Device_Table =
{
	EP_NUM,
	1
};

DEVICE_PROP Device_Property =
{
	USBiAP2_init,
	USBiAP2_Reset,
	USBiAP2_Status_In,
	USBiAP2_Status_Out,
	USBiAP2_Data_Setup,
	USBiAP2_NoData_Setup,
	USBiAP2_Get_Interface_Setting,
	USBiAP2_GetDeviceDescriptor,
	USBiAP2_GetConfigDescriptor,
	USBiAP2_GetStringDescriptor,
	0,
	0x40 // MAX PACKET SIZE
};

USER_STANDARD_REQUESTS User_Standard_Requests =
{
	USBiAP2_GetConfiguration,
	USBiAP2_SetConfiguration,
	USBiAP2_GetInterface,
	USBiAP2_SetInterface,
	USBiAP2_GetStatus,
	USBiAP2_ClearFeature,
	USBiAP2_SetEndPointFeature,
	USBiAP2_SetDeviceFeature,
	USBiAP2_SetDeviceAddress
};

ONE_DESCRIPTOR Device_Descriptor =
{
	(uint8_t*)USBiAP2_DeviceDescriptor,
	USBiAP2_DEVICE_DESC
};

ONE_DESCRIPTOR Config_Descriptor =
{
	(uint8_t*)USBiAP2_ConfigDescriptor,
	USBiAP2_SIZE_CONFIG_DESC
};

ONE_DESCRIPTOR USBD_CompatID_Descriptor = 
  {
    (uint8_t*)&USBD_CompatIDDesc,
    sizeof(USBD_CompatIDDescStruct)  
  };
ONE_DESCRIPTOR USBD_ExtProperties_Descriptor = 
  {
    (uint8_t*)USBD_ExtPropertiesDesc,
    sizeof(USBiAP2_WINUSB_EXT_PROP_DESC_SIZE) 
  };

ONE_DESCRIPTOR String_Descriptor[7];

static uint8_t *USBD_GetExtPropDescriptor(uint16_t Length);
static uint8_t *USBD_GetCompatIDDescriptor(uint16_t Length);

/*******************************************************************************
* Function Name  : USBiAP2_init.
* Description    : USBiAP2 init routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USBiAP2_init(void)
{

    String_Descriptor[USBD_IDX_LANGID_STR] 		= (ONE_DESCRIPTOR){(uint8_t*)USBiAP2_StringLangID, 		USBiAP2_StringLangID[0]};
	String_Descriptor[USBD_IDX_MFC_STR] 		= (ONE_DESCRIPTOR){(uint8_t*)USBiAP2_StringVendor, 		USBiAP2_StringVendor[0]};
	String_Descriptor[USBD_IDX_PRODUCT_STR] 	= (ONE_DESCRIPTOR){(uint8_t*)USBiAP2_StringProduct, 	USBiAP2_StringProduct[0]};
	String_Descriptor[USBD_IDX_SERIAL_STR] 		= (ONE_DESCRIPTOR){(uint8_t*)USBiAP2_StringSerial, 		USBiAP2_StringSerial[0]};
	String_Descriptor[USBD_IDX_INTERFACE_STR] 	= (ONE_DESCRIPTOR){(uint8_t*)USAiAP2_StringInterface, 	USAiAP2_StringInterface[0]};
	String_Descriptor[USBD_IDX_WINUSB_STR] 		= (ONE_DESCRIPTOR){(uint8_t*)USBD_StringWinUSB, 		USBD_StringWinUSB[0]};
	// String_Descriptor[5] = (ONE_DESCRIPTOR){(uint8_t*)USBiAP2_StringProtocol, USBiAP2_StringProtocol[0]};

	pInformation->Current_Configuration = 0;

	// Connect the device
	PowerOn();

	// Perform basic device initialization operations
	USB_SIL_Init();

	bDeviceState = UNCONNECTED;
}

/*******************************************************************************
* Function Name  : USBiAP2_Reset
* Description    : USBiAP2 reset routine
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USBiAP2_Reset(void)
{
	// DEVICE as not configured
	pInformation->Current_Configuration = 0;

	// Current Feature initialization
	pInformation->Current_Feature = 0;

	// Set Virtual_Com_Port DEVICE with the default Interface
	pInformation->Current_Interface = 1;

	SetBTABLE(BTABLE_ADDRESS);

	// Initialize endpoint 0
	SetEPType(ENDP0, EP_CONTROL);
	SetEPRxAddr(ENDP0, ENDP0_RXADDR);
	SetEPTxAddr(ENDP0, ENDP0_TXADDR);
	Clear_Status_Out(ENDP0);
	SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
	SetEPRxValid(ENDP0);

	// Initialize			EP1 -> OUT
	SetEPType(ENDP1, EP_BULK);
	SetEPRxAddr(ENDP1, ENDP1_RXADDR);
	SetEPRxCount(ENDP1, USBiAP2_EP1_RX_DATA_SIZE);
	SetEPRxStatus(ENDP1, EP_RX_VALID);
	SetEPTxStatus(ENDP1, EP_TX_DIS);

	// Initialize			IN <- EP2
	SetEPType(ENDP2, EP_BULK);
	SetEPTxAddr(ENDP2, ENDP2_TXADDR);
	SetEPTxStatus(ENDP2, EP_TX_NAK);
	SetEPRxStatus(ENDP2, EP_RX_DIS);

	// Initialize			EP3 -> OUT
	SetEPType(ENDP3, EP_BULK);
	SetEPRxAddr(ENDP3, ENDP3_RXADDR);
	SetEPRxCount(ENDP3, USBiAP2_EP3_RX_DATA_SIZE);
	SetEPRxStatus(ENDP3, EP_RX_VALID);
	SetEPTxStatus(ENDP3, EP_TX_DIS);

	// Initialize			IN <- EP4
	SetEPType(ENDP4, EP_BULK);
	SetEPTxAddr(ENDP4, ENDP4_TXADDR);
	SetEPTxStatus(ENDP4, EP_TX_NAK);
	SetEPRxStatus(ENDP4, EP_RX_DIS);

	// Set this device to response on default address
	SetDeviceAddress(0);

	bDeviceState = ATTACHED;
}

/*******************************************************************************
* Function Name  : USBiAP2_SetConfiguration.
* Description    : Update the device state to configured.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USBiAP2_SetConfiguration(void)
{
  DEVICE_INFO *pInfo = &Device_Info;

  if (pInfo->Current_Configuration != 0)
  {
    // Device configured
    bDeviceState = CONFIGURED;
  }
}

/*******************************************************************************
* Function Name  : USBiAP2_SetDeviceAddress.
* Description    : Update the device state to addressed.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USBiAP2_SetDeviceAddress (void)
{
  bDeviceState = ADDRESSED;
}


/*******************************************************************************
* Function Name  : USBiAP2_GetInterface.
* Description    : Update the device state to addressed.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
// void USBiAP2_GetInterface (void)
// {

// }

/*******************************************************************************
* Function Name  : USBiAP2_SetInterface.
* Description    : Update the device state to addressed.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
// void USBiAP2_SetInterface (void)
// {

// }


/*******************************************************************************
* Function Name  : USBiAP2_Status_In.
* Description    : Status In Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USBiAP2_Status_In(void)
{

}

/*******************************************************************************
* Function Name  : USBiAP2_Status_Out
* Description    : Status OUT Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USBiAP2_Status_Out(void)
{

}

/*******************************************************************************
* Function Name  : USBiAP2_Data_Setup
* Description    : handle the data class specific requests
* Input          : Request Nb.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
RESULT USBiAP2_Data_Setup(uint8_t RequestNo)
{
  uint8_t *(*CopyRoutine)(uint16_t);
  CopyRoutine = NULL;

  if (RequestNo == USB_REQ_GET_OS_FEATURE_DESCRIPTOR)
  {
	  if (pInformation->USBwIndexs.bw.bb0 == CustomHID_TYPE_OS_FEATURE_EXT_COMPAT_ID && pInformation->USBbmRequestType == 0xC0)
	  {
		  CopyRoutine = USBD_GetCompatIDDescriptor;
	  }
	  else if (pInformation->USBwIndexs.bw.bb0 == CustomHID_TYPE_OS_FEATURE_EXT_PROPERTIES && pInformation->USBbmRequestType == 0xC1)
	  {
		  CopyRoutine = USBD_GetExtPropDescriptor;
	  }
  }

  if (CopyRoutine == NULL)
  {
  	//Catches here on C0 request
    return USB_UNSUPPORT;
  }

  pInformation->Ctrl_Info.CopyData = CopyRoutine;
  pInformation->Ctrl_Info.Usb_wOffset = 0;
  (*CopyRoutine)(0);
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : USBiAP2_NoData_Setup.
* Description    : handle the no data class specific requests.
* Input          : Request No.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
RESULT USBiAP2_NoData_Setup(uint8_t RequestNo)
{
   return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : USBiAP2_GetDeviceDescriptor.
* Description    : Gets the device descriptor.
* Input          : Length.
* Output         : None.
* Return         : The address of the device descriptor.
*******************************************************************************/
uint8_t *USBiAP2_GetDeviceDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &Device_Descriptor);
}

/*******************************************************************************
* Function Name  : USBiAP2_GetConfigDescriptor.
* Description    : get the configuration descriptor.
* Input          : Length.
* Output         : None.
* Return         : The address of the configuration descriptor.
*******************************************************************************/
uint8_t *USBiAP2_GetConfigDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &Config_Descriptor);
}

/*******************************************************************************
* Function Name  : USBiAP2_GetStringDescriptor
* Description    : Gets the string descriptors according to the needed index
* Input          : Length.
* Output         : None.
* Return         : The address of the string descriptors.
*******************************************************************************/
uint8_t *USBiAP2_GetStringDescriptor(uint16_t Length)
{
	uint8_t wValue0 = pInformation->USBwValue0;
	if (wValue0 == 0xEE)
	{
		return Standard_GetDescriptorData(Length, &String_Descriptor[USBD_IDX_WINUSB_STR]);
	}
	if (wValue0 == USBD_IDX_LANGID_STR)
	{
		return Standard_GetDescriptorData(Length, &String_Descriptor[USBD_IDX_LANGID_STR]);
	}
	if (wValue0 == USBD_IDX_MFC_STR)
	{
		return Standard_GetDescriptorData(Length, &String_Descriptor[USBD_IDX_MFC_STR]);
	}
	if (wValue0 == USBD_IDX_PRODUCT_STR)
	{
		return Standard_GetDescriptorData(Length, &String_Descriptor[USBD_IDX_PRODUCT_STR]);
	}
	if (wValue0 == USBD_IDX_SERIAL_STR)
	{
		return Standard_GetDescriptorData(Length, &String_Descriptor[USBD_IDX_SERIAL_STR]);
	}
	if (wValue0 == USBD_IDX_INTERFACE_STR)
	{
		return Standard_GetDescriptorData(Length, &String_Descriptor[USBD_IDX_INTERFACE_STR]);
	}

	return NULL;
}

/*******************************************************************************
* Function Name  : USBiAP2_Get_Interface_Setting.
* Description    : test the interface and the alternate setting according to the
*                  supported one.
* Input1         : uint8_t: Interface : interface number.
* Input2         : uint8_t: AlternateSetting : Alternate Setting number.
* Output         : None.
* Return         : The address of the string descriptors.
*******************************************************************************/
RESULT USBiAP2_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
  if (AlternateSetting > 1)
  {
    return USB_UNSUPPORT;
  }
  else if (Interface > 1)
  {
    return USB_UNSUPPORT;
  }
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : USBD_GetExtPropDescriptor
* Description    : get the protocol value
* Input          : Length.
* Output         : None.
* Return         : address of the protocol value.
*******************************************************************************/
static uint8_t *USBD_GetExtPropDescriptor(uint16_t Length)
{
	return Standard_GetDescriptorData(Length, &USBD_ExtProperties_Descriptor);
}

/*******************************************************************************
* Function Name  : USBD_GetCompatIDDescriptor
* Description    : get the protocol value
* Input          : Length.
* Output         : None.
* Return         : address of the protocol value.
*******************************************************************************/
static uint8_t *USBD_GetCompatIDDescriptor(uint16_t Length)
{
	return Standard_GetDescriptorData(Length, &USBD_CompatID_Descriptor);
}
