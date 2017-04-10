/******************** (C) COPYRIGHT 2014 STMicroelectronics ********************
* File Name          : stc3100.h
* Author             : AMS team
* Version            : V1.2
* Date               : 2014/10
* Description        : Configuration & various feature implementation of STC3100
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


/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef __STC3100_H
#define __STC3100_H


/* Includes ------------------------------------------------------------------*/

/* Exported typedef-----------------------------------------------------------*/
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef char s8;
typedef short s16;
typedef long s32;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/* Exported define -----------------------------------------------------------*/

#define STC3100_SLAVE_ADDRESS        0xE0    /* STC3100 8-bit address byte */

/* ******************************************************************************** */
#define SENSERESISTOR  33    // sense resistor value in milliOhms (10min, 100max)
/*   TO BE DEFINED ACCORDING TO HARDWARE IMPLEMENTATION                             */
/* ******************************************************************************** */

#define STC3100_OK 0


/*Address of the STC3100 register --------------------------------------------*/
#define STC3100_REG_MODE                 0x00 /*Mode Register                 */
#define STC3100_REG_CTRL                 0x01 /*Control and Status Register   */
#define STC3100_REG_CHARGE_LOW           0x02 /*Gas Gauge Charge Data Bits 0-7*/
#define STC3100_REG_CHARGE_HIGH          0x03 /*Gas Gauge Charge Data Bits 8-15*/    
#define STC3100_REG_COUNTER_LOW          0x04 /*Number of Conversion Bits 0-7*/
#define STC3100_REG_COUNTER_HIGH         0x05 /*Number of Conversion Bits 8-15*/
#define STC3100_REG_CURRENT_LOW          0x06 /*Battery Current Value Bits 0-7*/
#define STC3100_REG_CURRENT_HIGH         0x07 /*Battery Current Value Bits 8-15*/
#define STC3100_REG_VOLTAGE_LOW          0x08 /*Battery Voltage Value Bits 0-7*/
#define STC3100_REG_VOLTAGE_HIGH         0x09 /*Battery Voltage Value Bits 8-15*/
#define STC3100_REG_TEMPERATURE_LOW      0x0A /*Temperature Values Bits 0-7) */
#define STC3100_REG_TEMPERATURE_HIGH     0x0B /*Temperature Values Bits 8-15)*/

/* Device ID registers Address 24 to 31 --------------------------------------*/
#define STC3100_REG_ID0                  0x18 /*Part Type ID 10h  */
#define STC3100_REG_ID1                  0x19 /*Unique Part ID Bits 0-7  */
#define STC3100_REG_ID2                  0x1A /*Unique Part ID Bits 8-15  */
#define STC3100_REG_ID3                  0x1B /*Unique Part ID Bits 16-23  */
#define STC3100_REG_ID4                  0x1C /*Unique Part ID Bits 24-31  */
#define STC3100_REG_ID5                  0x1D /*Unique Part ID Bits 32-39  */
#define STC3100_REG_ID6                  0x1E /*Unique Part ID Bits 40-47  */
#define STC3100_REG_ID7                  0x1F /*Device ID CRC  */

/*    General Purpose RAM Register Address 32-63     */
#define STC3100_RAM_SIZE      32  /*Total RAM register of STC3100*/

#define STC3100_REG_RAM0                               0x20  
#define STC3100_REG_RAM2                               0x22
#define STC3100_REG_RAM4                               0x24
#define STC3100_REG_RAM6                               0x26
#define STC3100_REG_RAM8                               0x28  
#define STC3100_REG_RAM12                              0x2C  
#define STC3100_REG_RAM14                              0x2E  
#define STC3100_REG_RAM16                              0x30  
#define STC3100_REG_RAM18                              0x32 
#define STC3100_REG_RAM20                              0x34 
#define STC3100_REG_RAM22                              0x36 
#define STC3100_REG_RAM24                              0x38 
#define STC3100_REG_RAM26                              0x3A 
#define STC3100_REG_RAM28                              0x3C 
#define STC3100_REG_RAM30                              0x3E 


/* Exported functions prototypes----------------------------------------------*/
//s8 STC3100_Read(u8, u8, u8 *);
int STC3100_ReadByte(u8);
int STC3100_ReadWord(u8);
//s8 STC3100_Write(u8 , u8 ,u8 *);
int STC3100_WriteByte(u8, u8);
int STC3100_WriteWord(u8, s16);
int STC3100_Startup(void);
int STC3100_Powerdown(void);
int ReadBatteryData(void);


/* STC3100 variables definition ------------------------------------*/

extern s16 s16_BattVoltage;     // battery voltage in mV
extern s16 s16_BattCurrent;     // battery current in mA
extern s16 s16_BattTemperature; // battery temperature in 0.1°C
extern s16 s16_BattChargeCount; // Coulomb counter value in mAh
extern s16 s16_BattCounter;     // conv counter




#endif /* __STC3100_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
