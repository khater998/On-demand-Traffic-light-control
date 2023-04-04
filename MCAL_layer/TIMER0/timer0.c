/******************************************************************************
 *
 * Module: TIMER0
 *
 * File Name: timer0.c
 *
 * Description: Source file for the ATmega32 TIMER0 driver
 *
 * Author: MOHAMED IBRAHIM
 *
 *******************************************************************************/

#include "timer0.h"

STD_ReturnType TIMER0_calc_ms(uint16 time_ms)
{
	STD_ReturnType error_status = E_OK;						/* to store the error value to be returned */
	SET_BIT(TCCR0, FOC0);
	/* Choose CTC mode */
	TIMER0_CTC_MODE_ENABLE();

	uint32 time_us = (uint32)time_ms * 1000;

	/* create a variable to store the number of ticks required */
	uint8 no_ticks  =  0 ;

	/* check if time required can be calculated without prescaler */
	if (time_us < TIMER0_NO_PRESCALER_OVF_TIME )
	{
		TIMER0_SET_PRESCALER(TIMER0_NO_PRESCALER);
		no_ticks = (uint8)(time_us / TIMER0_NO_PRESCALER_TICK_TIME);
	}

	/* check if time required can be calculated with prescaler of 8*/
	else if (time_us < TIMER0_PRESCALER_8_OVF_TIME)
	{
		TIMER0_SET_PRESCALER(TIMER0_PRESCALER_8);
		no_ticks = (uint8)(time_us / TIMER0_PRESCALER_8_TICK_TIME);
	}

	/* check if time required can be calculated with prescaler of 64*/
	else if(time_us < TIMER0_PRESCALER_64_OVF_TIME)
	{
		TIMER0_SET_PRESCALER(TIMER0_PRESCALER_64);
		no_ticks = (uint8)((time_us) / TIMER0_PRESCALER_64_TICK_TIME);
	}

	/* check if time required can be calculated with prescaler of 256*/
	else if(time_us < TIMER0_PRESCALER_256_OVF_TIME)
	{
		TIMER0_SET_PRESCALER(TIMER0_PRESCALER_256);
		no_ticks = (uint8)(time_us / TIMER0_PRESCALER_256_TICK_TIME);
	}

	/* check if time required can be calculated with prescaler of 1024*/
	else if (time_us < TIMER0_PRESCALER_1024_OVF_TIME)
	{
		TIMER0_SET_PRESCALER(TIMER0_PRESCALER_1024);
		no_ticks = (uint8)(time_us / TIMER0_PRESCALER_1024_TICK_TIME);
	}

	else
	{
		error_status = E_NOT_OK;
	}

	TCNT0 = 0;
	OCR0 = no_ticks;


	return error_status;
}
