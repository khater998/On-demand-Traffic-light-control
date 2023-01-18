/*
 * led.c
 *
 * Created: 08/01/2023 11:38:08 م
 *  Author: khater
 */ 


#include "led.h"
/*************************************************************************************************/
/*******************                  LED_init()          ****************************************/
/*************************************************************************************************/
EN_LED_error LED_init(led_t* led)
{
	/* create a variable to store the error type  */
	EN_LED_error error_type = LED_ok;
	/* create a variable to check for DIO error  */
	EN_DIO_error DIO_error_flag = DIO_ok;
	
	/* initialize the led and store the error return in DIO_error_flag  */
	DIO_error_flag = DIO_init(led->portNumber, led->pinNumber, OUTPUT);
	
	/* if there is an error from DIO  */
	if (DIO_error_flag != DIO_ok)
		/* set error_type to DIO_error  */
		error_type = DIO_error; 
	
	/* return error_type  */
	return error_type;
}
/*************************************************************************************************/
/*************************           check_initilization()       *********************************/
/*************************************************************************************************/
EN_LED_error check_initilization(led_t* led)
{
	/* create a variable to store the error_type  */
	EN_LED_error error_type = LED_ok;

	/* check if pin number is not legal  */
	if ((led->pinNumber) > 7 || (led->pinNumber) < 0)
	{
		/* return DIO_error error  */
		error_type = DIO_error;
	}
	
	/* create a variable to store the state */
	volatile uint8_t DDR_state = 0;
	
	/* Determine what port to be used */
	switch (led->portNumber)
	{
		case PORT_A:
		/* read pin state and store it in DDR_state  */
			DDR_state = READ_BIT(DDRA,led->pinNumber);
		break;
		
		/* repeat the same steps of port A to port B */
		case PORT_B:
			DDR_state = READ_BIT(DDRB,led->pinNumber);
		break;
		
		/* repeat the same steps of port A to port C */
		case PORT_C:
			DDR_state = READ_BIT(DDRC,led->pinNumber);
		break;
		
		/* repeat the same steps of port A to port D */
		case PORT_D:
			DDR_state = READ_BIT(DDRD,led->pinNumber);
		break;
		
		/* if user enters an invalid port name  */
		default:
		/* set error type to DIO_error error  */
			error_type = DIO_error;
		break;
	} 
	
	/* Give priority to DIO_error return */
	if (error_type != LED_ok)
		return error_type;
		
	/* if there is no DIO_error, update the error type if pin isn't initialized */
	if (DDR_state == 0)
		return error_type = LED_not_initialized;
	else 
		return error_type;
	
}
/*************************************************************************************************/
/****************************           LED_on()          ****************************************/
/*************************************************************************************************/
EN_LED_error LED_on(led_t* led)
{
	/* create a variable to store the error type  */
	EN_LED_error error_type = LED_ok;
	
	/* check if pin is initialized as OUTPUT before operating */
	error_type = check_initilization(led);
	
	/* if there is any error, don't do anything and return */
	if (error_type != LED_ok)
		return error_type;
	
	/* set the pin to the HIGH state  */
	DIO_write(led->portNumber, led->pinNumber, HIGH);
	
	/* return error_type, must be led_ok if writing is successful  */
	return error_type;
}
/*************************************************************************************************/
/***************************           LED_off()          ****************************************/
/*************************************************************************************************/
EN_LED_error LED_off(led_t* led)
{
	/* create a variable to store the error type  */
	EN_LED_error error_type = LED_ok;
	
	/* check if pin is initialized as OUTPUT before operating */
	error_type = check_initilization(led);
	
	/* if there is any error, don't do anything and return */
	if (error_type != LED_ok)
		return error_type;
	
	DIO_write(led->portNumber, led->pinNumber, LOW);
	
	/* return error_type  */
	return error_type;
}
/*************************************************************************************************/
/************************           LED_toggle()          ****************************************/
/*************************************************************************************************/
EN_LED_error LED_toggle(led_t* led)
{
	/* create a variable to store the error type  */
	EN_LED_error error_type = DIO_ok;
	
	/* check if pin is initialized as OUTPUT before operating */
	error_type = check_initilization(led);
	
	/* if there is any error, don't do anything and return */
	if (error_type != LED_ok)
		return error_type;
	
	DIO_toggle(led->portNumber, led->pinNumber);
	
	/* return error_type  */
	return error_type;
}
/*************************************************************************************************/
/********************           LED_read_state()          ****************************************/
/*************************************************************************************************/
EN_LED_error LED_read_state(led_t* led, uint8_t *state)
{
	/* create a variable to store the error type  */
	EN_LED_error error_type = LED_ok;
	
	/* check if pin is initialized as OUTPUT before operating */
	error_type = check_initilization(led);
	
	/* if there is any error, don't do anything and return */
	if (error_type != LED_ok)
		return error_type;
		
	DIO_read(led->portNumber,led->pinNumber, state);
	
	/* return error_type  */
	return error_type;
}

/*************************************************************************************************/
/*************************           LED_blink()          ****************************************/
/*************************************************************************************************/
EN_LED_error LED_blink_interruptCheck(led_t* led, uint8_t time_seconds)
{
	/* create a variable to store the error type  */
	EN_LED_error error_type = LED_ok;
	
	/* check if pin is initialized as OUTPUT before operating */
	error_type = check_initilization(led);
	
	/* if there is any error, don't do anything and return */
	if (error_type != LED_ok)
		return error_type;
	
	/* get the interrupt_triggered variable from app.c */
	extern uint8_t interrupt_triggered;
	
	/* create an iterator variable for the while loop */
	uint8_t interval  = 0;
	
	/* we will toggle state 4 times a second, so the loop repeate 4*seconds */
	while (interval < 4*time_seconds)
	{
		/* if interrupt is triggered, turn off LED and return from function */
		if (interrupt_triggered == 1)
		{
			DIO_write(led->portNumber, led->pinNumber, LOW);
			return error_type;
		}
		/* if not, toggle state and wait 0.25s, increase the iterator variable */
		DIO_toggle(led->portNumber, led->pinNumber);
		_delay_ms(250);
		interval++;
	}
	/* it time is up, turn off LED and return */
	DIO_write(led->portNumber, led->pinNumber, LOW);
	
	return error_type;
}
/*************************************************************************************************/
/*******************         blink_two_yellows()          ****************************************/
/*************************************************************************************************/
EN_LED_error blink_two_yellows(led_t* led1, led_t* led2, uint8_t time_seconds)
{
	/* create a variable to store the error type  */
	EN_LED_error error_type = LED_ok;
	
	/* check if pin is initialized as OUTPUT before operating */
	error_type = check_initilization(led1);
	/* if there is any error, don't do anything and return */
	if (error_type != LED_ok)
		return error_type;
	
	/* check if pin is initialized as OUTPUT before operating */
	error_type = check_initilization(led2);
	/* if there is any error, don't do anything and return */
	if (error_type != LED_ok)
		return error_type;
		
	/* create an iterator variable for the while loop */
	uint8_t interval  = 0;
	
	/* we will toggle state 2 times a second, so the loop repeate 2*seconds */
	while (interval < 2*time_seconds)
	{
		/* toggle LEDs every 0.5 seconds && increase iterator variable*/
		DIO_toggle(led1->portNumber, led1->pinNumber);
		DIO_toggle(led2->portNumber, led2->pinNumber);
		_delay_ms(500);
		interval++;
	}
	/* after finishing, turn off LEDs and return */
	DIO_write(led1->portNumber, led1->pinNumber, LOW);
	DIO_write(led2->portNumber, led2->pinNumber, LOW);
	return error_type;
}
/*************************************************************************************************/
/*******************         leds_on_temporary_interruptCheck()          *************************/
/*************************************************************************************************/
EN_LED_error leds_on_temporary_interruptCheck(led_t *led1, led_t *led2, uint8_t time_seconds)
{
	/* create a variable to store the error type  */
	EN_LED_error error_type = LED_ok;
	
	/* check if pin is initialized as OUTPUT before operating */
	error_type = check_initilization(led1);
	/* if there is any error, don't do anything and return */
	if (error_type != LED_ok)
		return error_type;
	
	/* check if pin is initialized as OUTPUT before operating */
	error_type = check_initilization(led2);
	/* if there is any error, don't do anything and return */
	if (error_type != LED_ok)
		return error_type;
	
	/* get the interrupt_triggered variable from app.c */
	extern uint8_t interrupt_triggered;
	
	/* turn on the required LEDs */
	DIO_write(led1->portNumber, led1->pinNumber, HIGH);
	DIO_write(led2->portNumber, led2->pinNumber, HIGH);
	
	/* create an iterator variable for the while loop */
	uint8_t interval = 0;
	
	/* check for interrupt 10 times every second */
	while (interval < 10*time_seconds)
	{
		/* if interrupt is triggered, turn off LEDs and return from function */
		if (interrupt_triggered == 1)
		{
			DIO_write(led1->portNumber, led1->pinNumber, LOW);
			DIO_write(led2->portNumber, led2->pinNumber, LOW);
			return;
		}
		/* if not, wait 0.1s, increase the iterator variable */
		_delay_ms(100);
		interval++;
	}
	/* it time is up, turn off LEDs and return */
	
	DIO_write(led1->portNumber, led1->pinNumber, LOW);
	DIO_write(led2->portNumber, led2->pinNumber, LOW);
	return error_type;
}
/*************************************************************************************************/
/*********************           LED_init_test()          ****************************************/
/*************************************************************************************************/
void LED_init_test()
{
	/* create two variables to check for the expected and actual error */
	volatile EN_LED_error expected_error;
	volatile EN_LED_error actual_error;
	
	/* create a led object to test on */
	led_t ledtest = {.portNumber = PORT_A, .pinNumber = 5};
		
	/* invoke the LED_init function for each test case */
	/* test case 1: valid data */
	expected_error = LED_ok;
	actual_error = LED_init(&ledtest);
	
	/* test case 2: entering an invalid port or pin THAT should cause DIO error*/
	ledtest.pinNumber = 10;
	expected_error = DIO_error;
	actual_error = LED_init(&ledtest);	
}
/*************************************************************************************************/
/***********************           check_initilization_test()          ***************************/
/*************************************************************************************************/
void check_initilization_test()
{
	/* create two variables to check for the expected and actual error */
	volatile EN_LED_error expected_error;
	volatile EN_LED_error actual_error;
	
	/* create a led object to test on */
	led_t ledtest = {.portNumber = PORT_A, .pinNumber = 9};
	
	/* test 1 : led with wrong port or pin number */
	/* invoke the check_initilization function  */
	expected_error = DIO_error;
	actual_error = check_initilization(&ledtest);
	
	/* test 2 : valid led pin && port numbers but not initialized */
	ledtest.pinNumber = 5;
	/* invoke the check_initilization function  */
	expected_error = LED_not_initialized;
	actual_error = check_initilization(&ledtest);
	
	/* test 3: led initialized */
	LED_init(&ledtest);
	/* invoke the check_initilization function  */
	expected_error = LED_ok;
	actual_error = check_initilization(&ledtest);
}
/*************************************************************************************************/
/***********************           LED_on_test()          ****************************************/
/*************************************************************************************************/
void LED_on_test()
{
	/* create two variables to check for the expected and actual error */
	volatile EN_LED_error expected_error;
	volatile EN_LED_error actual_error;
	
	/* create a led object to test on */
	led_t ledtest = {.portNumber = PORT_A, .pinNumber = 5};
	LED_init(&ledtest);
	
	/* invoke the LED_on function for each test case */
	/* test case 1: valid data */
	expected_error = LED_ok;
	actual_error = LED_on(&ledtest);
	
	/* test case 2: entering an invalid port or pin THAT should cause DIO error*/
	ledtest.portNumber = 'M';
	expected_error = DIO_error;
	actual_error = LED_on(&ledtest);
}
/*************************************************************************************************/
/**********************           LED_off_test()          ****************************************/
/*************************************************************************************************/
void LED_off_test()
{
	/* create two variables to check for the expected and actual error */
	volatile EN_LED_error expected_error;
	volatile EN_LED_error actual_error;

	/* create a led object to test on */
	led_t ledtest = {.portNumber = PORT_A, .pinNumber = 5};
	LED_init(&ledtest);
	
	/* invoke the LED_init function for each test case */
	/* test case 1: valid data */
	expected_error = LED_ok;
	actual_error = LED_off(&ledtest);
	
	/* test case 2: entering an invalid port or pin THAT should cause DIO error*/
	ledtest.pinNumber = 10;
	expected_error = DIO_error;
	actual_error = LED_off(&ledtest);
	
}
/*************************************************************************************************/
/*******************           LED_toggle_test()          ****************************************/
/*************************************************************************************************/
void LED_toggle_test()
{
	/* create two variables to check for the expected and actual error */
	volatile EN_LED_error expected_error;
	volatile EN_LED_error actual_error;
	
	/* create a led object to test on */
	led_t ledtest = {.portNumber = PORT_A, .pinNumber = 5};
	LED_init(&ledtest);
	
	/* invoke the LED_toggle function for each test case */
	/* test case 1: valid data */
	expected_error = LED_ok;
	actual_error = LED_toggle(&ledtest);
	
	/* test case 2: entering an invalid port or pin THAT should cause DIO error*/
	ledtest.pinNumber = 10;
	expected_error = DIO_error;
	actual_error = LED_toggle(&ledtest);
	
}
/*************************************************************************************************/
/*******************       LED_read_state_test()          ****************************************/
/*************************************************************************************************/
void LED_read_state_test()
{
	/* create two variables to check for the expected and actual error */
	volatile EN_LED_error expected_error;
	volatile EN_LED_error actual_error;
	
	/* create a led object to test on */
	led_t ledtest = {.portNumber = PORT_A, .pinNumber = 5};
	LED_init(&ledtest);
	
	/* create a variable to complete the function arguments*/
	uint8_t x;
	
	/* invoke the LED_read_state function for each test case */
	/* test case 1: valid data */
	expected_error = LED_ok;
	actual_error = LED_read_state(&ledtest,&x);
	
	
	/* test case 2: entering an invalid port or pin THAT should cause DIO error*/
	ledtest.pinNumber = 10;
	expected_error = DIO_error;
	actual_error = LED_read_state(&ledtest,&x);
}
/*************************************************************************************************/
/*******************       blink_two_yellows_test()          *************************************/
/*************************************************************************************************/
void blink_two_yellows_test()
{
	/* create two variables to check for the expected and actual error */
	volatile EN_LED_error expected_error;
	volatile EN_LED_error actual_error;
	led_t ledtest1 = {.portNumber = PORT_A, .pinNumber = 5};
	
	led_t ledtest2 = {.portNumber = PORT_A, .pinNumber = 7};
	LED_init(&ledtest2);
	
	
	/* invoke the blink_two_yellows function for each test case */
	/* test case 1: two valid LEDs but led1 is not initialized */
	expected_error = LED_not_initialized;
	actual_error = blink_two_yellows(&ledtest1, &ledtest2, 5);
	
	/* test case 2: two initialized LEDs but led2 has invalid pin number */
	LED_init(&ledtest1);
	ledtest2.pinNumber = 10;
	expected_error = DIO_error;
	actual_error = blink_two_yellows(&ledtest1, &ledtest2, 1);
	
	/* test case 3: all LEDs properties are valid*/
	ledtest2.pinNumber = 5;
	expected_error = LED_ok;
	actual_error = blink_two_yellows(&ledtest1, &ledtest2, 1);
	
}
/*************************************************************************************************/
/*******************       LED_blink_interruptCheck_test()          ******************************/
/*************************************************************************************************/
void LED_blink_interruptCheck_test()
{
	volatile EN_LED_error expected_error;
	volatile EN_LED_error actual_error;
	led_t ledtest = {.portNumber = PORT_A, .pinNumber = 5};
	
	/* invoke the LED_blink_interruptCheck function for each test case */
	/* test case 1: valid LED but is not initialized */
	expected_error = LED_not_initialized;
	actual_error = LED_blink_interruptCheck(&ledtest, 5);
	
	/* test case 2: two initialized LEDs but led2 has invalid pin number */
	LED_init(&ledtest);
	ledtest.pinNumber = 10;
	expected_error = DIO_error;
	actual_error = LED_blink_interruptCheck(&ledtest, 1);
	
	/* test case 3: all LEDs properties are valid*/
	ledtest.pinNumber = 5;
	expected_error = LED_ok;
	actual_error = LED_blink_interruptCheck(&ledtest, 1);
	
	
}
/*************************************************************************************************/
/*******************       leds_on_temporary_interruptCheck_test()    ****************************/
/*************************************************************************************************/
void leds_on_temporary_interruptCheck_test()
{
	/* create two variables to check for the expected and actual error */
	volatile EN_LED_error expected_error;
	volatile EN_LED_error actual_error;
	led_t ledtest1 = {.portNumber = PORT_A, .pinNumber = 5};
	
	led_t ledtest2 = {.portNumber = PORT_B, .pinNumber = 5};
	LED_init(&ledtest2);
	
	/* invoke the leds_on_temporary_interruptCheck function for each test case */
	/* test case 1: two valid LEDs but led1 is not initialized */
	expected_error = LED_not_initialized;
	actual_error = leds_on_temporary_interruptCheck(&ledtest1, &ledtest2, 5);
	
	/* test case 2: two initialized LEDs but led2 has invalid pin number */
	LED_init(&ledtest1);
	ledtest2.pinNumber = 10;
	expected_error = DIO_error;
	actual_error = leds_on_temporary_interruptCheck(&ledtest1, &ledtest2, 1);
	
	/* test case 3: all LEDs properties are valid*/
	ledtest2.pinNumber = 5;
	expected_error = LED_ok;
	actual_error = leds_on_temporary_interruptCheck(&ledtest1, &ledtest2, 1);
	
}

