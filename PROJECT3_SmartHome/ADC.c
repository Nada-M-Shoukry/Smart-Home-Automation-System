/*
 * ADC.c
 *
 *  Created on: Oct 7, 2024
 *      Author: nadam
 */

/***************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "common_macros.h"
#include "ADC.h"

/*******************Global Variables****************************/

 volatile uint16 Digital_value = 0;

/*******************ISR Definitions****************************/

ISR(ADC_vect)
{
	/* Read ADC Data after conversion complete */
	Digital_value = ADC;
}

/*****************Functions Definition************************/

void ADC_init(void)
{
	ADMUX |= (1<<REFS0) | (1<<REFS1);  /* ADMUX Register Bits Description:
	                                    * REFS1:0 = 11 to choose to connect internal 2.56 voltage reference
	                                    * ADLAR   = 0 right adjusted
	                                    * MUX4:0  = 00000 to choose channel 0 as initialization */



	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);  /* ADCSRA Register Bits Description:
	                                                             * ADEN    = 1 Enable ADC
	                                                             * ADIE    = 0 Enable ADC Interrupt
	                                                             * ADATE   = 0 Disable Auto Trigger
	                                                             * ADPS2:0 = 111
	                                                             * to choose ADC_Clock = F_CPU/128 = 16Mhz/128 = 125Khz
	                                                             * ADC must operate in range 50-200Khz */

}

uint16 ADC_readChannel (uint8 channel_num)
{
	channel_num &= 0x07;           /* Input channel number must be from 0 --> 7 */

	ADMUX &= 0xE0;                /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */

	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */

	SET_BIT(ADCSRA, ADSC);      /* Start conversion write '1' to ADSC */

	while( BIT_IS_CLEAR (ADCSRA, ADIF) );  /* Wait for conversion to be completed and flag is set to '1' */

	SET_BIT (ADCSRA, ADIF);  /* Set flag bit to '1' to clear flag for next conversions. */

	return ADC;             /* Read the converted digital value from the data register. */
}


