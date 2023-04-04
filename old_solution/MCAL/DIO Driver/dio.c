/*
 * DIO_Driver.c
 *
 * Created: 08/01/2023 11:21:42 م
 *  Author: khater
 */ 


#include "DIO.h"
/*************************************************************************************************/
/*******************               DIO_init()          *******************************************/
/*************************************************************************************************/
EN_DIO_error DIO_init(volatile uint8_t portNumber, volatile uint8_t pinNumber, uint8_t direction)		// initialize a pin as INPUT OR OUTPUT
{
	/* create a variable to store the error type  */
	EN_DIO_error error_type = DIO_ok;
	
	/* check if pin number is not legal  */
	if (pinNumber > 7 || pinNumber < 0)
	{
		/* return undefined pin error  */	
		error_type = undefined_pin;
		return error_type;
	}
	
	/* check which port to be used  */
	switch(portNumber)
	{
		case PORT_A:
			/* if direction is INPUT, set that pin to 0  */
			if (direction == INPUT)
			{
				CLR_BIT(DDRA,pinNumber);		// DDRA &= ~(1<<pinNumber)
			}
			/* else if direction is OUTPUT, set that pin to 1  */
			else if (direction == OUTPUT)
			{
				SET_BIT(DDRA,pinNumber);		// DDRA |= (1<<pinNumber);
			}
			else
			/* if user entered a false direction other than input(0) or output(1)  */
			{
				error_type = undefined_direction;
			}
		break;
		
		/* repeat the same steps of port A to port B */
		case PORT_B:
			if (direction == INPUT)
			{
				CLR_BIT(DDRB,pinNumber);		// DDRB &= ~(1<<pinNumber);
			}
			else if (direction == OUTPUT)
			{
				SET_BIT(DDRB,pinNumber);		// DDRB |= (1<<pinNumber);
			}
			else
			{
				error_type = undefined_direction;
			}
		break;
		
		/* repeat the same steps of port A to port C */
		case PORT_C:
			if (direction == INPUT)
			{
				CLR_BIT(DDRC,pinNumber);		// DDRC &= ~(1<<pinNumber);
			} 
			else if (direction == OUTPUT)
			{
				SET_BIT(DDRC,pinNumber);		// DDRC |= (1<<pinNumber);
			}
			else
			{
				// error handling
				error_type = undefined_direction;
			}
		break;

		/* repeat the same steps of port A to port D */
		case PORT_D:
			if (direction == INPUT)
			{
				CLR_BIT(DDRD,pinNumber);		// DDRD &= ~(1<<pinNumber);
			}
			else if (direction == OUTPUT)
			{
				SET_BIT(DDRD,pinNumber);		// DDRD |= (1<<pinNumber);
			}
			else
			{
				error_type = undefined_direction;
			}
		break;
		
		/* if user enters an invalid port name  */
		default:
			/* set error type to undefined port error  */
			error_type = undefined_port;
		break;
	}
	/* return error type */
	return error_type;
}
/*************************************************************************************************/
/*******************                 DIO_write()          ****************************************/
/*************************************************************************************************/
EN_DIO_error DIO_write(volatile uint8_t portNumber, volatile uint8_t pinNumber, uint8_t state) 			// set a pin as HIGH OR LOW
{
	/* create a variable to store the error type  */
	EN_DIO_error error_type = DIO_ok;
	
	/* check if pin number is not legal  */
	if (pinNumber > 7 || pinNumber < 0)
	{
		/* set error_type to undefined pin  */
		error_type = undefined_pin;
		return error_type;
	}
	
	/* check which port to be used  */
	switch (portNumber)
	{
		case PORT_A:
			/* if state is LOW, set that pin to 0  */
			if (state == LOW)
			{
				CLR_BIT(PORTA,pinNumber);		// PORTA &= ~(1<<pinNumber);
			}
			/* else if state is HIGH, set that pin to 1  */
			else if (state == HIGH)
			{
				SET_BIT(PORTA,pinNumber);		// PORTA |= (1<<pinNumber);
			}
			else
			/* if user entered a false state other than LOW or HIGH  */
			{
				/* set error type to undefined port error  */
				error_type = undefined_state;
			}
		break;
		
		/* repeat the same steps of port A to port B */
		case PORT_B:
			if (state == LOW)
			{
				CLR_BIT(PORTB,pinNumber);		// PORTB &= ~(1<<pinNumber);
			}
			else if (state == HIGH)
			{	
				SET_BIT(PORTB,pinNumber);		// PORTB |= (1<<pinNumber);
			}
			else
			{
				error_type = undefined_state;
			}
		break;
		
		/* repeat the same steps of port A to port C */
		case PORT_C:
			if (state == LOW)
			{
				CLR_BIT(PORTC,pinNumber);		// PORTC &= ~(1<<pinNumber);
			}
			else if (state == HIGH)
			{
				SET_BIT(PORTC,pinNumber);		// PORTC |= (1<<pinNumber);
			}
			else
			{
				error_type = undefined_state;
			}
		break;
		
		/* repeat the same steps of port A to port D */
		case PORT_D:
			if (state == LOW)
			{
				CLR_BIT(PORTD,pinNumber);		// PORTD &= ~(1<<pinNumber);
			}
			else if (state == HIGH)
			{
				SET_BIT(PORTD,pinNumber);		// PORTD |= (1<<pinNumber);
			}
			else
			{
				error_type = undefined_state;
			}
			
		break;
		/* if user enters an invalid port name  */
		default:
			/* set error type to undefined port error  */
			error_type = undefined_port;
		break;
	}
	/* return error type */
	return error_type;
}
/*************************************************************************************************/
/*******************               DIO_toggle()          *****************************************/
/*************************************************************************************************/
EN_DIO_error DIO_toggle(volatile uint8_t portNumber, volatile uint8_t pinNumber)						// toggles a bit state
{
	/* create a variable to store the error type  */
	EN_DIO_error error_type = DIO_ok;
	
	/* check if pin number is not legal  */
	if (pinNumber > 7 || pinNumber < 0)
	{
		/* return undefined pin error  */
		error_type = undefined_pin;
		return error_type;
	}
	
	/* check which port to be used  */
	switch(portNumber)
	{
		
		case PORT_A:
			/* toggle the required pin  */
			TOGGLE_BIT(PORTA, pinNumber);		// PORTA ^= (1<<pinNumber);
		break;
		
		/* repeat the same steps of port A to port B */
		case PORT_B:
			TOGGLE_BIT(PORTB, pinNumber);		// PORTB ^= (1<<pinNumber);
		break;
		
		/* repeat the same steps of port A to port C */
		case PORT_C:
			TOGGLE_BIT(PORTC, pinNumber);		// PORTC ^= (1<<pinNumber);
		break;
		
		/* repeat the same steps of port A to port D */
		case PORT_D:
			TOGGLE_BIT(PORTD, pinNumber);		// PORTD ^= (1<<pinNumber);
		break;
		
		/* if user enters an invalid port name  */
		default:
			/* set error type to undefined port error  */
			error_type = undefined_port;
		break;
	}
	/* return error type */
	return error_type;
}
/*************************************************************************************************/
/*******************               DIO_read()          *******************************************/
/*************************************************************************************************/
EN_DIO_error DIO_read(volatile uint8_t portNumber, volatile uint8_t pinNumber, uint8_t * state)		// get the pin state
{
	/* create a variable to store the error type  */
	EN_DIO_error error_type = DIO_ok;
	
	/* check if pin number is not legal  */
	if (pinNumber > 7 || pinNumber < 0)
	{
		/* return undefined pin error  */
		error_type = undefined_pin;
		return error_type;
	}
	
	/* check which port to be used  */
	switch(portNumber)
	{
		case PORT_A:
			/* read pin state and store it in state variable  */
			*state = (PINA & (1<<pinNumber)) >>pinNumber;		// read pin state
		break;
		
		/* repeat the same steps of port A to port B */
		case PORT_B:
			*state = (PINB & (1<<pinNumber)) >>pinNumber;
		break;
		
		/* repeat the same steps of port A to port C */
		case PORT_C:
			*state = (PINC & (1<<pinNumber)) >>pinNumber;
		break;
		
		/* repeat the same steps of port A to port D */
		case PORT_D:
			*state = (PIND & (1<<pinNumber)) >>pinNumber;
		break;
		
		/* if user enters an invalid port name  */
		default:
			/* set error type to undefined port error  */
			error_type = undefined_port;
		break;
	}
	/* return error type */
	return error_type;
}
/*************************************************************************************************/
/*******************               DIO_init_test()          **************************************/
/*************************************************************************************************/
void DIO_init_test()
{
	/* create two variables to check for the expected and actual error */
	volatile EN_DIO_error expected_error;
	volatile EN_DIO_error actual_error;
	
	/* invoke the DIO_init function for each test case */
	/* test case 1: valid data */
	expected_error = DIO_ok;
	actual_error = DIO_init(PORT_A,5,OUTPUT);
	
	/* test case 2: entering an invalid port */
	expected_error = undefined_port;
	actual_error = DIO_init('K',5,OUTPUT);
	
	/* test case 3: entering an invalid pin number */
	expected_error = undefined_pin;
	actual_error = DIO_init('B',9,OUTPUT);
	
	/* test case 4: entering an invalid direction */
	expected_error = undefined_direction; 
	actual_error = DIO_init(PORT_B,5,2);	
}

/*************************************************************************************************/
/*******************               DIO_write_test()       ****************************************/
/*************************************************************************************************/
void DIO_write_test()
{
	/* create two variables to check for the expected and actual error */
	volatile EN_DIO_error expected_error;
	volatile EN_DIO_error actual_error;
	
	/* invoke the DIO_write function for each test case */
	/* test case 1: valid data */
	expected_error = DIO_ok;
	actual_error = DIO_write(PORT_A,5,HIGH);
	
	/* test case 2: entering an invalid port */
	expected_error = undefined_port;
	actual_error = DIO_write('K',5,HIGH);
	
	/* test case 3: entering an invalid pin number */
	expected_error = undefined_pin;
	actual_error = DIO_write('B',9,LOW);
	
	/* test case 4: entering an invalid state */
	expected_error = undefined_state;
	actual_error = DIO_write(PORT_B,5,2);
	
}
/*************************************************************************************************/
/*******************               DIO_toggle_test()          ************************************/
/*************************************************************************************************/
void DIO_toggle_test()
{
	/* create two variables to check for the expected and actual error */
	volatile EN_DIO_error expected_error;
	volatile EN_DIO_error actual_error;
	
	/* invoke the DIO_toggle function for each test case */
	/* test case 1: valid data */
	expected_error = DIO_ok;
	actual_error = DIO_toggle(PORT_A,5);
	
	/* test case 2: entering an invalid port */
	expected_error = undefined_port;
	actual_error = DIO_toggle('K',5);
	
	/* test case 3: entering an invalid pin number */
	expected_error = undefined_pin;
	actual_error = DIO_toggle('B',9);
	
}
/*************************************************************************************************/
/*******************               DIO_read_test()          **************************************/
/*************************************************************************************************/
void DIO_read_test()
{
	/* create two variables to check for the expected and actual error */
	volatile EN_DIO_error expected_error;
	volatile EN_DIO_error actual_error;
	
	/* create a variable to complete the function arguments*/
	uint8_t x;
	
	/* invoke the DIO_read function for each test case */
	/* test case 1: valid data */
	expected_error = DIO_ok;
	actual_error = DIO_read(PORT_A,5,&x);
	
	/* test case 2: entering an invalid port */
	expected_error = undefined_port;
	actual_error = DIO_read('K',5,&x);
	
	/* test case 3: entering an invalid pin number */
	expected_error = undefined_pin;
	actual_error = DIO_read('B',9,&x);
	
}