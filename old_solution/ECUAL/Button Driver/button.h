/*
 * button.h
 *
 * Created: 08/01/2023 11:28:50 م
 *  Author: khater
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../MCAL/DIO Driver/dio.h"
#include "../../UTILITY/registers.h"
#include "../../UTILITY/STD_types.h"
#include "../../UTILITY/bit_operations.h"

#include <avr/interrupt.h>
#include "../../MCAL/INTERRUPT Driver/interrupt.h"



/* Create a button data type */
typedef struct
{
	uint8_t portNumber;
	uint8_t pinNumber;
	}button_t;

// button error types
typedef enum
{
	BUTTON_ok,
	BUTTON_DIO_error,
}EN_BUTTON_error;


EN_BUTTON_error BUTTON_init(button_t* btn);							// set button pin as input
EN_BUTTON_error BUTTON_read(button_t* btn, uint8_t * state);		// read button state 

void BUTTON_init_test();
void BUTTON_read_test();



#endif /* BUTTON_H_ */