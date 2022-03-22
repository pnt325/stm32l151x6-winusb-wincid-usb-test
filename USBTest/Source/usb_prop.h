/**
  ******************************************************************************
  * @file    usb_prop.h
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   All processing related to Virtual COM Port Demo (Endpoint 0)
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

#ifndef __USB_PROP_H__
#define __USB_PROP_H__

#define USBiAP2_GetConfiguration								NOP_Process
#define USBiAP2_GetInterface								    NOP_Process
#define USBiAP2_SetInterface								    NOP_Process
#define USBiAP2_GetStatus										    NOP_Process
#define USBiAP2_ClearFeature									  NOP_Process
#define USBiAP2_SetEndPointFeature   						NOP_Process
#define USBiAP2_SetDeviceFeature								NOP_Process
//#define USBiAP2_SetConfiguration							NOP_Process
//#define USBiAP2_SetDeviceAddress							NOP_Process
#define  CustomHID_TYPE_OS_FEATURE_EXT_PROPERTIES           5
#define  CustomHID_TYPE_OS_FEATURE_EXT_COMPAT_ID            4

void USBiAP2_init(void);
void USBiAP2_Reset(void);

void USBiAP2_SetConfiguration(void);
void USBiAP2_SetDeviceAddress (void);
// void USBiAP2_GetInterface (void);
// void USBiAP2_SetInterface (void);

void USBiAP2_Status_In (void);
void USBiAP2_Status_Out (void);
RESULT USBiAP2_Data_Setup(uint8_t);
RESULT USBiAP2_NoData_Setup(uint8_t);
RESULT USBiAP2_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);

uint8_t *USBiAP2_GetDeviceDescriptor(uint16_t );
uint8_t *USBiAP2_GetConfigDescriptor(uint16_t);
uint8_t *USBiAP2_GetStringDescriptor(uint16_t);

#endif // __USB_PROP_H__

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

