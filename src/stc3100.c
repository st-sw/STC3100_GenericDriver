/******************** (C) COPYRIGHT 2014 STMicroelectronics ********************
* File Name          : stc3100.c
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


/* Includes ------------------------------------------------------------------*/
#include "stc3100.h"
#include "stc31xx_I2cCustomReadWrite.h"

/* Private define ------------------------------------------------------------*/
//#define STC3100_OK 0

/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/


/* Private  Variables ---------------------------------------*/
s16 s16_BattVoltage;     // battery voltage in mV
s16 s16_BattCurrent;     // battery current in mA
s16 s16_BattTemperature; // battery Temperature in 0.1°C
s16 s16_BattChargeCount; // battery charge in mA.h
s16 s16_BattCounter;     // conv counter

/* Private functions ---------------------------------------------------------*/






/* --- constants ---------------------------------------------------------- */

#define CurrentFactor  (48210/SENSERESISTOR) 
// LSB=11.77uV/R= ~48210/R/4096 - convert to mA

#define ChargeCountFactor  (27443/SENSERESISTOR)
// LSB=6.7uVh/R ~27443/R/4096 - converter to mAh

#define VoltageFactor  9994  
// LSB=2.44mV ~9994/4096 - convert to mV

#define TemperatureFactor  5120  
// LSB=0.125°C ~5120/4096 - convert to 0.1°C



/*******************************************************************************
* Function Name  : conv
* Description    : conversion utility 
*  convert a raw 16-bit value from STC3100 registers into user units (mA, mAh, mV, °C)
*  (optimized routine for efficient operation on 8-bit processors such as ST7/STM8)
* Input          :s16_value, u16_factor
* Return         : result = value * factor / 4096
*******************************************************************************/
static s16 conv(s16 s16_value, u16 u16_factor)
{
	return( ( (s32) s16_value * u16_factor ) >> 12 );
}






/*******************************************************************************
* Function Name  : STC3100_ReadByte
* Description    : utility function to read the value stored in one register
* Input          : u8_register: STC3100 register,
* Return         : 8-bit value, or 0 if error
*******************************************************************************/
int STC3100_ReadByte(u8 Addr)
{
	s8 s8_value;
	u8 pu8_data[2];
	int res;

	res=STC3100_Read(1, Addr, pu8_data);

	if (res == STC3100_OK)
	{
		// no error
		s8_value = pu8_data[0];
	}
	else
	{
		return (int)(-1); //error
	}

	return(s8_value);
}


/*******************************************************************************
* Function Name  : STC3100_ReadWord
* Description    : utility function to read the value stored in a register pair
* Input          : u8_register: STC3100 register,
* Return         : 16-bit value, or 0 if error
*******************************************************************************/
int STC3100_ReadWord(u8 Addr)
{
	s16 s16_value;
	u8 pu8_data[2];
	int res;

	res=STC3100_Read(2, Addr, pu8_data);

	if (res == STC3100_OK)
	{
		// no error
		s16_value = pu8_data[0];
		s16_value |= ((s16)pu8_data[1]) << 8;
	}
	else
	{
		return (int)(-1); //error
	}

	return(s16_value);
}



/*******************************************************************************
* Function Name  : STC3100_WriteByte
* Description    : utility function to write a 8-bit value into a register
* Input          : u8_register: STC3100 register, u8_value: 8-bit value to write
* Return         : error status (STC3100_OK, !STC3100_OK)
*******************************************************************************/
int STC3100_WriteByte(u8 u8_Register, u8 u8_value)
{
	int res;
	u8 pu8_data[2];

	pu8_data[0]=u8_value; 
	res = STC3100_Write(1, u8_Register, pu8_data);
	
	if (res == STC3100_OK)
	{
		// Ok, no error
		res = 0;
	}
	else
	{
		res = (int)(-1); //error
	}

	return(res);
}


/* -----------------------------------------------------------------
----------------------------------------------------------------- */
/*******************************************************************************
* Function Name  : STC3100_WriteWord
* Description    : utility function to write a 16-bit value into one register pair
* Input          : u8_register: STC3100 register, s16_value: 16-bit value to write
* Return         : error status (STC3100_OK, !STC3100_OK)
*******************************************************************************/
int STC3100_WriteWord(u8 u8_Register, s16 s16_value)
{
	int res;
	u8 pu8_data[2];

	pu8_data[0]=s16_value & 0xFF; 
	pu8_data[1]=s16_value>>8; 
	res = STC3100_Write(2, u8_Register, pu8_data);

	if (res == STC3100_OK)
	{
		// Ok, no error
		res = 0;
	}
	else
	{
		res = (int)(-1); //error
	}

	return(res);
}



/*******************************************************************************
* Function Name  : STC3100_Startup
* Description    :  initialize and start the STC3100 at application startup
* Input          : None
* Return         : error status (STC3100_OK, !STC3100_OK)
*******************************************************************************/
int STC3100_Startup(void)
{
	int s32_res;

	// first, check the presence of the STC3100 by reading first byte of dev. ID
	s32_res = STC3100_ReadByte(STC3100_REG_ID0);
	if (s32_res!= 0x10) return (-1);

	// read the REG_CTRL to reset the GG_EOC and VTM_EOC bits
	STC3100_ReadByte(STC3100_REG_CTRL);

	// write 0x02 into the REG_CTRL to reset the accumulator and counter and clear the PORDET bit,
	s32_res = STC3100_WriteByte(STC3100_REG_CTRL, 0x02);
	if (s32_res!= STC3100_OK) return (s32_res);

	// then 0x10 into the REG_MODE register to start the STC3100 in 14-bit resolution mode.
	s32_res = STC3100_WriteByte(STC3100_REG_MODE, 0x10);
	if (s32_res!= STC3100_OK) return (s32_res);

	return (STC3100_OK);
}


/*******************************************************************************
* Function Name  : STC3100_Powerdown
* Description    :  stop the STC3100 at application power down
* Input          : None
* Return         : error status (STC3100_OK, !STC3100_OK)
*******************************************************************************/
int STC3100_Powerdown(void)
{
	int s32_res;

	// write 0 into the REG_MODE register to put the STC3100 in standby mode
	s32_res = STC3100_WriteByte(STC3100_REG_MODE, 0);
	if (s32_res!= STC3100_OK) return (s32_res);

	return (STC3100_OK);
}




/*******************************************************************************
* Function Name  : ReadBatteryData
* Description    :  utility function to read the battery data from STC3100
*                  to be called every 2s or so
* Input          : None
* Return         : error status (STC3100_OK, !STC3100_OK)
* Affect         : global battery variables
*******************************************************************************/
int ReadBatteryData(void)
{
	u8 pu8_data[12];
	int s32_res;
	s16 s16_value;

	// read STC3100 registers 0 to 11
	s32_res=STC3100_Read(12, 0, pu8_data);
	if (s32_res!=STC3100_OK) return(s32_res);  // read failed

	// fill the battery status data

	// charge count
	s16_value=pu8_data[3]; s16_value = (s16_value<<8) + pu8_data[2];
	s16_BattChargeCount = conv(s16_value,ChargeCountFactor);  // result in mAh

	// conversion counter
	s16_value=pu8_data[5]; s16_value = (s16_value<<8) + pu8_data[4];
	s16_BattCounter = s16_value;

	// current
	s16_value=pu8_data[7]; s16_value = (s16_value<<8) + pu8_data[6];
	s16_value &= 0x3fff; // mask unused bits
	if (s16_value>=0x2000) s16_value -= 0x4000;  // convert to signed value
	s16_BattCurrent = conv(s16_value,CurrentFactor);  // result in mA

	// voltage
	s16_value=pu8_data[9]; s16_value = (s16_value<<8) + pu8_data[8];
	s16_value &= 0x0fff; // mask unused bits
	if (s16_value>=0x0800) s16_value -= 0x1000;  // convert to signed value
	s16_BattVoltage = conv(s16_value,VoltageFactor);  // result in mV

	// temperature
	s16_value=pu8_data[11]; s16_value = (s16_value<<8) + pu8_data[10];
	s16_value &= 0x0fff; // mask unused bits
	if (s16_value>=0x0800) s16_value -= 0x1000;  // convert to signed value
	s16_BattTemperature = conv(s16_value,TemperatureFactor);  // result in 0.1°C

	return(STC3100_OK);
}





/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
