
==========================================
1.	Introduction
==========================================

This code example is released to support the use of the STC3100 in customer applications..


==========================================
2.	Content
==========================================

stc3100.c	STC3100 access functions
stc3100.h	STC3100 definitions and function prototypes
stc31xx_I2cCustomReadWrite.h		prototypes of i2c primitives

The value of the sense resistor used with the STC3100 is defined as SENSERESISTOR in stc3100.h.

The I2C primitives must be adapted to the target system by editing the i2c.h header 
and the STC3100_Read/Write functions in the stc3100.c file.


==========================================
3.	Exported functions and variables
==========================================

Datatypes:
u8 and u16 are unsigned 8 bit and 16 bit integer types respectively, 
s8 and s16 are signed 8 bit and 16 bit integer types respectively, 
s32 is a signed 32 bit type.

Functions:
s8 STC3100_Startup(void);  	// initializes and starts the STC3100
s8 STC3100_Powerdown(void);	// stops and puts the STC3100 in power down
s8 ReadBatteryData(void);	// read the data from the STC3100, converts the raw values to user units.

Global variables:
s16 s16_BattVoltage;     // battery voltage in mV
s16 s16_BattCurrent;     // battery current in mA
s16 s16_BattTemperature; // battery temperature in 0.1°C
s16 s16_BattChargeCount; // Coulomb counter value in mAh

