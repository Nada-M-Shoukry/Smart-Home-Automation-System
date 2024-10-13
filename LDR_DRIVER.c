/*
 * LDR_DRIVER.c
 *
 *  Created on: Oct 8, 2024
 *      Author: nadam
 */
/*****************************************************/

#include "LDR_DRIVER.h"
#include "GPIO.h"
#include "ADC.h"
#include "common_macros.h"

/*****************Functions Definition***************/

uint16 LDR_getLightIntensity(void)
{
	uint16 light_value = 0;

	uint16 adc_value = 0;

	GPIO_setupPinDirection (PORTA_ID, PIN0_ID, PIN_INPUT);

	adc_value = ADC_readChannel( LDR_SENSOR_CHANNEL_ID);

	light_value = (uint16)( ((uint32) adc_value * 100) / 1024 );  /*convert light internsity value to percentage */

	return light_value;
}



