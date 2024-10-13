/*
 * ADC.h
 *
 *  Created on: Oct 7, 2024
 *      Author: nadam
 */
/**************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/**************************Definitions*************************************/

#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE    2.56

/**************************External Variables******************************/

extern volatile uint16 Digital_value;

/********************Function Prototypes*********************************/

void ADC_init(void);

/* Function Description :
 * Function responsible for initialize the ADC driver. */

uint16 ADC_readChannel (uint8 channel_num);

/* Function Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver. */


#endif /* ADC_H_ */
