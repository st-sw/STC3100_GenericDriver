# STC3100_GenericDriver
STC3100 fuel gauge Open source generic driver
(STC3100 Generic Driver)

Device under test:
----------------
Device:       STC3100 Battery Gas gage.  
Manufacturer: STMicroelectronics

Hardware:
----------------
Can be used on any platform with I2C Master (pin SCL & SDA) connected to I2C Slave of STC3100 device.  <br />
For instance: STM32 Nucleo board, STM32 discovery board, Arduino, ...  <br />

The STC3100 is designed to be power supplied directly from the battery. In this case, the STC3100 remains active even if the whole platform is in standby or powered off.


SW Requirements:
----------------
Implement the I2C driver depending on your platform.

