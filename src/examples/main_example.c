
/* Includes ------------------------------------------------------------------*/
#include "stc3100.h" 
#include "stc31xx_I2cCustomReadWrite.h"
#include <stdio.h> //for printf()


/* Private functions ---------------------------------------------------------*/
static int GasGaugeTimerFinished(void);


int main(void)
{
	int status;
	int LoopCount = 200; //arbitrary value for example


	status = I2c_CustomInit();
	if( status != 0)  return -1; //error


	status = STC3100_Startup();
	if( status != STC3100_OK)  return -1; //error

	//Get the battery status during few minutes (in this example), and then Power down the gas gauge.
	while(LoopCount > 0)
	{

		if(GasGaugeTimerFinished() == 1) //every 2s or more
		{
			LoopCount--;

			// read the data from the STC3100, converts the raw values to user units.
			status = ReadBatteryData();

			if (status == STC3100_OK)
			{
				/* results available */
				printf("Battery voltage (mV): %d\n", s16_BattVoltage);
				printf("Battery current (mA): %d\n", s16_BattCurrent);
				printf("Battery temperature (0.1°C): %d\n", s16_BattTemperature);
				printf("Coulomb counter value (mAh): %d\n", s16_BattChargeCount);
				printf("convertion counter: %d\n", s16_BattCounter);
				printf("\n");
			}
			else //error occured
			{
				printf("Error with ReadBatteryData\n");
			}
		}
		else
		{
			//Do other Tasks here ...
		}
	}

	status = STC3100_Powerdown();	// stops and puts the STC3100 in power down
	if( status != STC3100_OK)  return -1; //error

	return 0;
}



#define TIMER_LIMIT 0x5000 //arbitrary value to modify

static int GasGaugeTimerFinished(void)
{
	static unsigned int i = 1;

	i--;
	if( i == 0)
	{
		i = TIMER_LIMIT;
		return 1;
	}
	else
	{
		return 0;
	}
}

