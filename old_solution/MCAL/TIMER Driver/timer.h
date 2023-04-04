/*
 * timer.h
 *
 * Created: 11/01/2023 02:20:50 ص
 *  Author: khater
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "../DIO Driver/dio.h"
#include "../../UTILITY/registers.h"
#include "../../UTILITY/STD_types.h"
#include "../../UTILITY/bit_operations.h"


typedef enum timerMode
{
	normal,
	pwmPhaseCorrect,
	ctc,
	fastPWM
}timerMode_t;

typedef enum timerClock
{
	none,
	clk_1,
	clk_8,
	clk_64,
	clk_256,
	clk_1024,
	externalFalling,
	externalRising
}timerClock_t;

void TIMER0_init(timerMode_t mode, uint8_t initialValue);       // SET TIMER0 mode and initial value
void TIMER0_start(timerClock_t clock_prescaler);				// start timer0
void TIMER0_stop();
uint8_t TIMER0_state();											// check overflow




#endif /* TIMER_H_ */