/*
 * button.c
 *
 * Created: 08/01/2023 11:28:37 م
 *  Author: khater
 */ 


#include "button.h"
/*************************************************************************************************/
/*******************                  BUTTON_init()          *************************************/
/*************************************************************************************************/
EN_BUTTON_error BUTTON_init(button_t* btn)
{
	/* create a variable to store the error type  */
	EN_BUTTON_error error_type = BUTTON_ok;
	/* create a variable to check for DIO error  */
	EN_DIO_error DIO_error_flag = DIO_ok;
	
	/* Initialize Button port as INPUT*/
	DIO_error_flag = DIO_init(btn->portNumber,btn->pinNumber,INPUT);     
	/* if there is an error from DIO  */
	if (DIO_error_flag != DIO_ok)
		/* set error_type to DIO_error  */
		error_type = BUTTON_DIO_error;
	
	/* return error_type  */
	return error_type;
}

/*************************************************************************************************/
/*******************                  BUTTON_read()          *************************************/
/*************************************************************************************************/
EN_BUTTON_error BUTTON_read(button_t* btn, uint8_t *state)
{
	/* create a variable to store the error type  */
	EN_BUTTON_error error_type = BUTTON_ok;
	/* create a variable to check for DIO error  */
	EN_DIO_error DIO_error_flag = DIO_ok;
	
	/* Read Button state */
	DIO_error_flag = DIO_read(btn->portNumber,btn->pinNumber, state);	/* Reads Button state */
	/* if there is an error from DIO  */
	if (DIO_error_flag != DIO_ok)
		/* set error_type to DIO_error  */
		error_type = BUTTON_DIO_error;
	
	/* return error_type  */
	return error_type;
}
/*************************************************************************************************/
/*******************                  BUTTON_init_test()          ********************************/
/*************************************************************************************************/
void BUTTON_init_test()
{
	/* create two variables to check for the expected and actual error */
	volatile EN_BUTTON_error expected_error;
	volatile EN_BUTTON_error actual_error;
	
	/* create a BUTTON object to test on */
	button_t btntest = {.portNumber = PORT_A, .pinNumber = 5};
		
	/* test case 1: valid data */
	expected_error = BUTTON_ok;
	actual_error = BUTTON_init(&btntest);
	
	/* test case 2: invalid pin Number */
	btntest.pinNumber = 10;
	expected_error = BUTTON_DIO_error;
	actual_error = BUTTON_init(&btntest);
	
	
}

/*************************************************************************************************/
/*******************                  BUTTON_read_test()          ********************************/
/*************************************************************************************************/
void BUTTON_read_test()
{
	/* create two variables to check for the expected and actual error */
	volatile EN_BUTTON_error expected_error;
	volatile EN_BUTTON_error actual_error;
	
	uint8_t state;
	
	/* create a BUTTON object to test on */
	button_t btntest = {.portNumber = PORT_A, .pinNumber = 5};
	
	/* test case 1: valid data */
	expected_error = BUTTON_ok;
	actual_error = BUTTON_read(&btntest, &state);
	
	/* test case 2: invalid pin Number */
	btntest.pinNumber = 10;
	expected_error = BUTTON_DIO_error;
	actual_error = BUTTON_read(&btntest, &state);
	
}