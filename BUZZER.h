/*
 * BUZZER.h
 *
 *  Created on: Oct 9, 2024
 *      Author: nadam
 */
/**********************************************/
#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"

/***************Definitions********************/

#define BUZZER_PORT_ID      PORTD_ID
#define BUZZER_PIN_ID       PIN3_ID

/************Functions Prototype**************/

 void Buzzer_init(void);

 void Buzzer_on(void);

 void Buzzer_off(void);

#endif /* BUZZER_H_ */
