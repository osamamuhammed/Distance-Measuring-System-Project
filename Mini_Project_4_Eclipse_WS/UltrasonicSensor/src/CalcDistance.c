/******************************************************************************
 *
 * Description: Program to test HC-SR04 sensor with icu and display output on LCD
 *
 * Author: Osama M. Shehata
 *
 *******************************************************************************/
#include "lcd.h"
#include "avr/io.h" // To enable global interrupts using SREG register
#include "common_macros.h"
#include "ultrasosnicSensor.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
uint16 distance;

int main(void) {
	// Enable global interrupt I-bit
	SET_BIT(SREG, 7);

	// Intialize LCD
	LCD_init();

	//Display "Distance =   cm" at the beggining
	LCD_displayString("Distance =   cm");

	//intialize ultrasonic sensor
	Ultrasonic_init();

	while (1) {
		// Update value of distance variable using ultrasonic readings
		distance = Ultrasonic_readDistance();

		//Display the new readings on the LCD
		LCD_moveCursor(0, 10);
		LCD_intgerToString(distance);
	}

}
