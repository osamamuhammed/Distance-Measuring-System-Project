/******************************************************************************
 *
 * Module: Ultrasosnic Sensor
 *
 * File Name: Ultrasosnic Sensor.h
 *
 * Description: Source file for the HC-SR04 sensor
 *
 * Author: Osama M. Shehata
 *
 *******************************************************************************/
#include "icu.h"
#include "gpio.h"
#include "std_types.h"
#include "common_macros.h"
#include <util/delay.h>
#include "ultrasosnicSensor.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;
boolean g_echo_recieved = FALSE;
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/* Description:
 ➢ Initialize the ICU driver as required.
 ➢ Setup the ICU call back function.
 ➢ Setup the direction for the trigger pin as output pin through the GPIO driver.
 • Inputs: None
 • Return: None
 */
void Ultrasonic_init(void) {
	/* Create ICU configurations structure of type ICU_ConfigType
	 * 1. Frequency: F_CPU/8
	 * 2. Detect rising edge as the first edge
	 */
	ICU_ConfigType ICU_Configuration = { F_CPU_8, RISING };

	// Setup callback function to call Ultrasonic_edgeProcessing function
	ICU_setCallBack(Ultrasonic_edgeProcessing);

	//Initializa the ICU driver with the predefined configurations
	ICU_init(&ICU_Configuration);

	// Setup the direction for the trigger pin as output pin through the GPIO driver.
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT_ID,
	ULTRASONIC_TRIGGER_PIN_ID, PIN_OUTPUT);

}

/* Description:
 ➢ Send the Trigger pulse to the ultrasonic.
 • Inputs: None
 • Return: None
 */
void Ultrasonic_Trigger(void) {
	//Transmit a high pulse for 10 us to the ultrasonic sensor
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID,
	LOGIC_HIGH);
	_delay_us(10);	//Delay 10 us
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID,
	LOGIC_LOW);

}

/* Description:
 ➢ Send the trigger pulse by using Ultrasonic_Trigger function.
 ➢ Start the measurements by the ICU from this moment.
 • Inputs: None
 • Return: The measured distance in Centimeter.
 */
uint16 Ultrasonic_readDistance(void) {
	uint16 distance;
	Ultrasonic_Trigger();
	while (g_echo_recieved != TRUE)
		;
	distance = (((float)(SPEED_OF_SOUND)* (g_timeHigh*10) * EXECUTE_TIME)/2)-55;

	//reset global variables
	g_timeHigh = 0;
	g_echo_recieved = FALSE;

	return distance;

}

void Ultrasonic_edgeProcessing(void) {
	g_edgeCount++;
	if (g_edgeCount == 1) {
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		ICU_clearTimerValue();
		/* Detect falling edge */
		ICU_setEdgeDetectionType(FALLING);
	} else if (g_edgeCount == 2) {
		/* Store the High time value */
		g_timeHigh = ICU_getInputCaptureValue();
		/* Detect rising edge */
		ICU_setEdgeDetectionType(RISING);
		g_edgeCount = 0;	//Reset edge counter
		g_echo_recieved = TRUE;	// Raise echo recieved flag
	}
}
