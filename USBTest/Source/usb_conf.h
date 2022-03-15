/**
  ******************************************************************************
  * @file    usb_conf.h
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Virtual COM Port Demo configuration  header
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

#ifndef __USB_CONF_H__
#define __USB_CONF_H__

#define EP_NUM									(5)

#define BTABLE_ADDRESS						(0x000)

// TX/RX buffer base address
#define ENDP0_RXADDR							(0x040)
#define ENDP0_TXADDR							(0x080)
#define ENDP1_RXADDR							(0x0C0)
#define ENDP2_TXADDR							(0x100)
#define ENDP3_RXADDR							(0x180)
#define ENDP4_TXADDR							(0x140)

// IMR_MSK - mask defining which events has to be handled by the device application software
#define IMR_MSK (CNTR_CTRM | /*CNTR_WKUPM | */CNTR_ERRM  | CNTR_SOFM | CNTR_RESETM )		//CNTR_ESOFM | CNTR_SUSPM

//#define CTR_CALLBACK
//#define DOVR_CALLBACK
//#define ERR_CALLBACK
//#define WKUP_CALLBACK
//#define SUSP_CALLBACK
//#define RESET_CALLBACK
//#define SOF_CALLBACK
//#define ESOF_CALLBACK

// CTR service routines associated to defined endpoints
#define  EP1_IN_Callback   NOP_Process
//#define  EP2_IN_Callback   NOP_Process
#define  EP3_IN_Callback   NOP_Process
//#define  EP4_IN_Callback   NOP_Process
#define  EP5_IN_Callback   NOP_Process
#define  EP6_IN_Callback   NOP_Process
#define  EP7_IN_Callback   NOP_Process

//#define  EP1_OUT_Callback   NOP_Process
#define  EP2_OUT_Callback   NOP_Process
//#define  EP3_OUT_Callback   NOP_Process
#define  EP4_OUT_Callback   NOP_Process
#define  EP5_OUT_Callback   NOP_Process
#define  EP6_OUT_Callback   NOP_Process
#define  EP7_OUT_Callback   NOP_Process

#endif // __USB_CONF_H__

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
