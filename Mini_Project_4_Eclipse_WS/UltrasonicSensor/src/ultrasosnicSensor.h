/******************************************************************************
 *
 * Module: HC-SR04 sensor
 *
 * File Name: HC_SR04_sensor.h
 *
 * Description: Header file for the HC-SR04 sensor
 *
 * Author: Osama M. Shehata
 *
 *******************************************************************************/

#ifndef ULTRASOSNICSENSOR_H_
#define ULTRASOSNICSENSOR_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ULTRASONIC_TRIGGER_PORT_ID 		PORTB_ID
#define ULTRASONIC_TRIGGER_PIN_ID 		PIN5_ID
#define SPEED_OF_SOUND 34000		// speed in cm/sec
#define EXECUTE_TIME 0.000001

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Description:
 ➢ Initialize the ICU driver as required.
 ➢ Setup the ICU call back function.
 ➢ Setup the direction for the trigger pin as output pin through the GPIO driver.
 • Inputs: None
 • Return: None
 */
void Ultrasonic_init(void);


/* Description:
 ➢ Send the Trigger pulse to the ultrasonic.
 • Inputs: None
 • Return: None
 */
void Ultrasonic_Trigger(void);


/* Description:
 ➢ Send the trigger pulse by using Ultrasonic_Trigger function.
 ➢ Start the measurements by the ICU from this moment.
 • Inputs: None
 • Return: The measured distance in Centimeter.
 */
uint16 Ultrasonic_readDistance(void);


/* Description:
 ➢ This is the call back function called by the ICU driver.
 ➢ This is used to calculate the high time (pulse time) generated by the ultrasonic sensor.
 • Inputs: None
 • Return: None
 */
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASOSNICSENSOR_H_ */
