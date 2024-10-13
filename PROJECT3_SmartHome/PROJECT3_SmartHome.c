/*
 * PROJECT(3)_SmartHome.c
 *
 *  Created on: Oct 8, 2024
 *      Author: nadam
 */
#include "PROJECT3_SmartHome.h"


int main (void)
{
	SET_BIT (SREG, 7);  /*Activate global interrupt enable */

	LCD_init();
	ADC_init();
	DcMotor_Init();
	LEDS_init();
	FlameSensor_init();
	Buzzer_init();

	LCD_displayStringRowColumn(0, 0,  "Fan is  ");
	LCD_displayStringRowColumn(1, 0,  "Temp=   LDR=    ");

	uint8 LDR_intensity = 0 ;
	uint8 LM35_Temperature = 0 ;

	while(1)
	{
		LDR_intensity = LDR_getLightIntensity() ;
		LM35_Temperature = LM35_getTemperature();

		/**************************Temperature Adjustments************************/

		LM35_Temperature = (LM35_Temperature>70)? 70 : LM35_Temperature ; /* Adjust LM35 maximum temp. 70C */

		if (! (LM35_Temperature < 25) )
		{
			LCD_displayStringRowColumn( 0 , 7 , "ON " );
		}

		if(LM35_Temperature >= 40)
				{
					DcMotor_Rotate( CW , 100 );
				}
				else if (LM35_Temperature >= 35 && LM35_Temperature < 40 )
				{
					DcMotor_Rotate( CW , 75 );
				}
				else if (LM35_Temperature >= 30 && LM35_Temperature < 35)
				{
					DcMotor_Rotate( CW , 50 );
				}
				else if (LM35_Temperature >= 25 && LM35_Temperature < 30)
				{
					DcMotor_Rotate( CW , 25 );
				}
		else
		{
			DcMotor_Rotate( STOP , 0 );
			LCD_displayStringRowColumn( 0 , 7 , "OFF" );
		}

		LCD_moveCursor(1 , 5);
		LCD_intgerToString( (uint32) LM35_Temperature) ;
		LCD_displayStringRowColumn(1,7," ");


		/*********************Light Intensity adjustments**************/

		if(LDR_intensity <= 15 )
		{
			LED_ON( BLUE_LED  );
			LED_ON( RED_LED   );
			LED_ON( GREEN_LED );

		}
		else if (LDR_intensity <= 50)
		{
			LED_OFF( BLUE_LED  );
			LED_ON ( RED_LED   );
			LED_ON ( GREEN_LED );

		}
		else if (LDR_intensity <= 70)
		{
			LED_ON ( RED_LED   );
			LED_OFF( GREEN_LED );
			LED_OFF( BLUE_LED  );
		}
		else
		{
			LED_OFF( RED_LED   );
			LED_OFF( GREEN_LED );
			LED_OFF( BLUE_LED  );
		}

		LCD_moveCursor(1,12);
		if(LDR_intensity == 100 )
		{
			LCD_intgerToString( (uint32)LDR_intensity ) ;
		}
		else
		{
			LCD_intgerToString( (uint32)LDR_intensity ) ;
			LCD_displayCharacter(' ');
		}
		LCD_moveCursor(1,15);
		LCD_displayCharacter('%');



		/**************************Fire Alarm adjustments************************/

		if (FlameSensor_getValue() )   /* In case of Fire */
		{
			LCD_clearScreen();
			LCD_moveCursor (0, 1);
			LCD_displayString("CRITICAL ALERT!");
			Buzzer_on();        /* Activate Buzzer in case of Fire */

			while (FlameSensor_getValue() );  /* wait until the flame is off */

			Buzzer_off();

			LCD_clearScreen() ;

			LCD_displayStringRowColumn(0,0,"Fan is  ");

			LCD_displayStringRowColumn(1,0,"Temp=   LDR=    ");

			LCD_moveCursor(1 , 5);

			LCD_intgerToString( (uint32) LM35_Temperature );

			LCD_moveCursor(1 , 12);

			LCD_intgerToString( (uint32) LDR_intensity );

			LCD_moveCursor(1 , 15);

			LCD_displayCharacter('%');
		}
	}
}
