/*
 * LCD.c
 *
 *  Created on: Oct 7, 2024
 *      Author: nadam
 */
/*****************************************************************************/

#include "LCD.h"
#include "GPIO.h"
#include "common_macros.h"
#include <util/delay.h>

/************************Functions Definition********************************/

void LCD_init(void)
{
	GPIO_setupPinDirection (LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection (LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);

	GPIO_setupPortDirection (LCD_DATA_PORT_ID, PORT_OUTPUT);

	_delay_ms(20);     // LCD power ON delay always > 15ms.

	LCD_sendCommand (LCD_TWO_LINES_EIGHT_BITS_MODE); //use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode
	LCD_sendCommand (LCD_CURSOR_OFF);               //CURSOR OFF.
	LCD_sendCommand (LCD_CLEAR_COMMAND);           //CLEAR LCD.
}

void LCD_sendCommand (uint8 command)
{
	GPIO_writePin (LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW); /* Instruction Mode RS=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */


	GPIO_writePin (LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_writePort (LCD_DATA_PORT_ID, command); /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */

	GPIO_writePin (LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

}

void LCD_displayCharacter (uint8 data)
{
	GPIO_writePin (LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH); /* Instruction Mode RS=1 */
	_delay_ms(1); /* delay for processing Tas = 50ns */


	GPIO_writePin (LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_writePort (LCD_DATA_PORT_ID, data); /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */

	GPIO_writePin (LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

}

void LCD_displayString (const char *str)
{
	while (*str != '\0')
	{
		LCD_displayCharacter (*str);
		str++;
	}

}

void LCD_moveCursor (uint8 row, uint8 col)
{
	uint8 lcd_memory_address;

	switch (row)
	{
	case 0 :

		lcd_memory_address = col;

		break;

	case 1 :

		lcd_memory_address = col + 0x40;

		break;

	case 2 :

		lcd_memory_address = col + 0x10;

		break;

	case 3 :

		lcd_memory_address = col + 0x50;

		break;
	}

	LCD_sendCommand ( lcd_memory_address | LCD_SET_CURSOR_LOCATION);  //Move LCD cursor to this location.
}

void LCD_displayStringRowColumn (uint8 row, uint8 col, const char *str)
{
	LCD_moveCursor (row, col); //Go to this location on LCD screen.
	LCD_displayString (str);  //Display this string.
}

void LCD_intgerToString (int data)
{
	char buff[16];              //String to hold ASCII of the data.
	itoa (data, buff, 10);     //itoa -> C Function to convert data to its corresponding ASCII, 10 for Decimal.
	LCD_displayString (buff);
}

void LCD_clearScreen (void)
{
	LCD_sendCommand (LCD_CLEAR_COMMAND);
}
