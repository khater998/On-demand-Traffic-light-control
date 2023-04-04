/*
 * DIO_Driver.h
 *
 * Created: 08/01/2023 11:21:25 م
 *  Author: khater
 */ 


#ifndef DIO_H_
#define DIO_H_


#include "../../UTILITY/registers.h"
#include "../../UTILITY/STD_types.h"
#include "../../UTILITY/bit_operations.h"


// Defining port numbers
#define PORT_A 'A'
#define PORT_B 'B'
#define PORT_C 'C'
#define PORT_D 'D'

// defining port directions
#define INPUT 0
#define OUTPUT 1

// defining pin states
#define LOW 0
#define HIGH 1

// DIO expected errors
typedef enum
{
	DIO_ok,
	undefined_port,
	undefined_pin,
	undefined_direction,
	undefined_state
	}EN_DIO_error;
	

EN_DIO_error DIO_init(volatile uint8_t portNumber, volatile uint8_t pinNumber, uint8_t direction);		// initialize a pin as INPUT OR OUTPUT
EN_DIO_error DIO_write(volatile uint8_t portNumber, volatile uint8_t pinNumber, uint8_t state);			// set a pin as HIGH OR LOW
EN_DIO_error DIO_toggle(volatile uint8_t portNumber, volatile uint8_t pinNumber);						// toggles a bit state
EN_DIO_error DIO_read(volatile uint8_t portNumber, volatile uint8_t pinNumber, uint8_t * state);		// get the pin state

void DIO_init_test();
void DIO_write_test();
void DIO_toggle_test();
void DIO_read_test();


#endif /* DIO DRIVER_H_ */