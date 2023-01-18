/*
 * led.h
 *
 * Created: 08/01/2023 11:38:18 م
 *  Author: khater
 */ 


#ifndef LED_H_
#define LED_H_


#include "../../MCAL/DIO Driver/dio.h"
#include "../../MCAL/TIMER Driver/timer.h"
#include "../../UTILITY/registers.h"
#include "../../UTILITY/STD_types.h"
#include "../../UTILITY/bit_operations.h"
#define F_CPU 1000000
#include <util/delay.h>

/* Create a led data type */
typedef struct
{
	uint8_t portNumber;
	uint8_t pinNumber;
	}led_t;
	
// led error types
typedef enum
{
	LED_ok,
	DIO_error,
	LED_not_initialized
	}EN_LED_error;

EN_LED_error LED_init(led_t* led);								// Initializes led pin as OUTPUT 
EN_LED_error LED_on(led_t* led);								// SET led pin to HIGH state
EN_LED_error LED_off(led_t* led);								// SET led pin to LOW state
EN_LED_error LED_toggle(led_t* led);							// Toggles pin state
EN_LED_error LED_read_state(led_t* led, uint8_t *state);
EN_LED_error check_initilization(led_t* led);					// checks if user initialized the pin before writing to it

// created specially for the project
EN_LED_error blink_two_yellows(led_t* led1, led_t* led2, uint8_t time_seconds);		// for Pedestrian mode, toggles every 0.5 seconds
EN_LED_error LED_blink_interruptCheck(led_t* led, uint8_t time_seconds);			// for normal mode, Toggles pin state every 0.25 seconds for the specified time, with interrupt check
EN_LED_error leds_on_temporary_interruptCheck(led_t *led1, led_t *led2, uint8_t time_seconds);     //for normal mode, added an interrupt check 

void LED_init_test();
void check_initilization_test();	
void LED_on_test();
void LED_off_test();
void LED_toggle_test();
void LED_read_state_test();
					

void blink_two_yellows_test();
void LED_blink_interruptCheck_test();	
void leds_on_temporary_interruptCheck_test();

#endif /* LED_H_ */