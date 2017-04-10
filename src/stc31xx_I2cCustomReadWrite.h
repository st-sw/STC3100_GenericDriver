/******************** (C) COPYRIGHT 2014 STMicroelectronics ********************
* File Name          : stc31xx_I2cCustomReadWrite.h
* Author             : AMS - AAS application
* Version            : V2
* Date               : 2014/10
* Description        : gas gauge firmware for STC31xx
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

* THIS SOURCE CODE IS PROTECTED BY A LICENSE.
* FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED
* IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
*******************************************************************************/

#define STC31xx_I2C_OK 0
#define STC31xx_I2C_ERROR 1
#define STC31xx_I2C_ERR_BUFFER 2

#ifdef __cplusplus
extern "C"
{
#endif

	int STC3100_Write(unsigned char ByteCount, unsigned char RegisterAddr , unsigned char * TxBuffer);
	int STC3100_Read(unsigned char ByteCount, unsigned char RegisterAddr , unsigned char * RxBuffer);
	int I2c_CustomInit(void);

#ifdef __cplusplus
}
#endif

