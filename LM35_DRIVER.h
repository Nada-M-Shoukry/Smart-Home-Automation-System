/*
 * LM35_DRIVER.h
 *
 *  Created on: Oct 8, 2024
 *      Author: nadam
 */
/****************************************************/

#ifndef LM35_DRIVER_H_
#define LM35_DRIVER_H_

#include "std_types.h"

/*********************Definitons*********************/

#define SENSOR_PORT_ID 			  PORTA_ID
#define SENSOR_PIN_ID 			  PIN1_ID

#define SENSOR_CHANNEL_ID         1
#define SENSOR_MAX_VOLT_VALUE     1.5
#define SENSOR_MAX_TEMPERATURE    150
#define SENSOR_MIN_TEMPERATURE    0

/***************Functions Prototypes****************/

uint8 LM35_getTemperature(void);

#endif /* LM35_DRIVER_H_ */
