/*
 * interrupt.c
 *
 * Created: 09/01/2023 07:56:22 م
 *  Author: khater
 */ 

#include "interrupt.h"
/*************************************************************************************************/
/*******************            EXT_INT0_triggerControl()       **********************************/
/*************************************************************************************************/
EN_INTERRUPT_error EXT_INT0_triggerControl(triggerControl_t trigger_condition)
{
	/* create a variable to store the error type  */
	EN_INTERRUPT_error error_type = INTERRUPT_ok;
	
	/* if user enters a false trigger condition  */
	if (trigger_condition > 3 || trigger_condition < 0)
	{
		/* set error_type to undefined_trigger_condition  */
		return error_type = undefined_trigger_condition;
	}
	
	/* CLEAR ISC00 && ISC01 (responsible for trigger control of interrupt 0)  */
	/* load ISC00 && ISC01 with the relevant trigger  */
	MCUCR	= (MCUCR & 0xFC) | (trigger_condition);				/* trigger condition values are 0,1,2,3
											   if it's 0 then nothing will change, we have already CLEARED ISC00 and ISC01
											   else if it's 1 then ISC00 will be set to 1
											   else if it's 2 then ISC01 will be set to 1
											   else if if it's 3 then both ISC00 and ISC01 will be set to 1 */ 
	return error_type;
}
/*************************************************************************************************/
/*******************               EXT_INT1_triggerControl()       *******************************/
/*************************************************************************************************/
EN_INTERRUPT_error EXT_INT1_triggerControl(triggerControl_t trigger_condition)
{
	/* create a variable to store the error type  */
	EN_INTERRUPT_error error_type = INTERRUPT_ok;
	
	/* if user enters a false trigger condition  */
	if (trigger_condition > 3 || trigger_condition < 0)
	{
		/* set error_type to undefined_trigger_condition  */
		return error_type = undefined_trigger_condition;
	}
	
	/* trigger conditions for interrupt 1 are the same as of interrupt 0  */
	/* the only difference is that ISC10 && ISC11 are shifted two bits of ISC00 && ISC01 */
	/* So, we shift the trigger condition twice, then, we use OR  */
	MCUCR	= (MCUCR & 0XF3) | ((trigger_condition << 2));																
	
	return error_type;
}

/*************************************************************************************************/
/*******************               EXT_INT2_triggerControl()       *******************************/
/*************************************************************************************************/
EN_INTERRUPT_error EXT_INT2_triggerControl(triggerControl_INT2_t trigger_condition)
{
	/* create a variable to store the error type  */
	EN_INTERRUPT_error error_type = INTERRUPT_ok;
	
	/* if user enters a false trigger condition  */
	if (trigger_condition > 1 || trigger_condition < 0)
	{
		/* set error_type to undefined_trigger_condition  */
		return error_type = undefined_trigger_condition;
	}
	
	/* interrupt 2 has only 2 trigger conditions (falling or rising edge) */
	/* So, if it's falling edge, we clear the bit */
	if(trigger_condition == FALLING_EDGE_INT2)
		CLR_BIT(MCUCSR,6);
	/* otherwise, we set the bit */
	else if (trigger_condition == RISING_EDGE_INT2)
		SET_BIT(MCUCSR,6);
		
	return error_type;
}
/*************************************************************************************************/
/*******************         EXT_INT0_triggerControl_test()   ************************************/
/*************************************************************************************************/
void EXT_INT0_triggerControl_test()
{
	/* create two variables to check for the expected and actual error */
	volatile EN_INTERRUPT_error expected_error;
	volatile EN_INTERRUPT_error actual_error;
	
	/* invoke the EXT_INT0_triggerControl function for each test case */
	/* test case 1: valid data */
	expected_error = INTERRUPT_ok;
	actual_error = EXT_INT0_triggerControl(RISING_EDGE);
	
	/* test case 2: entering an trigger condition */
	expected_error = undefined_trigger_condition;
	actual_error = EXT_INT0_triggerControl(8);
	
}
/*************************************************************************************************/
/*******************         EXT_INT1_triggerControl_test()       ********************************/
/*************************************************************************************************/
void EXT_INT1_triggerControl_test()
{
	/* create two variables to check for the expected and actual error */
	volatile EN_INTERRUPT_error expected_error;
	volatile EN_INTERRUPT_error actual_error;
	
	/* invoke the EXT_INT1_triggerControl function for each test case */
	/* test case 1: valid data */
	expected_error = INTERRUPT_ok;
	actual_error = EXT_INT1_triggerControl(ANY_LOGICAL);
	
	/* test case 2: entering an trigger condition */
	expected_error = undefined_trigger_condition;
	actual_error = EXT_INT1_triggerControl(8);
}
/*************************************************************************************************/
/*******************         EXT_INT2_triggerControl_test()       ********************************/
/*************************************************************************************************/
void EXT_INT2_triggerControl_test()
{
	/* create two variables to check for the expected and actual error */
	volatile EN_INTERRUPT_error expected_error;
	volatile EN_INTERRUPT_error actual_error;
	
	/* invoke the EXT_INT3_triggerControl function for each test case */
	/* test case 1: valid data */
	expected_error = INTERRUPT_ok;
	actual_error = EXT_INT2_triggerControl(RISING_EDGE_INT2);
	
	/* test case 2: entering an trigger condition */
	expected_error = undefined_trigger_condition;
	actual_error = EXT_INT2_triggerControl(2);
}

