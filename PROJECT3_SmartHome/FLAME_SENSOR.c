/*
 * FLAME_SENSOR.c
 *
 *  Created on: Oct 9, 2024
 *      Author: nadam
 */
/**************************************************/

#include "FLAME_SENSOR.h"
#include "GPIO.h"


/***************Functions Definition**************/

void FlameSensor_init(void)
{
	GPIO_setupPinDirection (FLAME_SENSOR_PORT_ID, FLAME_SENSOR_PIN_ID, PIN_INPUT);
}

uint8 FlameSensor_getValue(void)
{
	uint8 flameSensor_value = 0;

	flameSensor_value = GPIO_readPin (FLAME_SENSOR_PORT_ID, FLAME_SENSOR_PIN_ID);

	return flameSensor_value;
}


