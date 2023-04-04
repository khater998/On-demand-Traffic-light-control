/******************************************************************************
 *
 * Module: APP
 *
 * File Name: app.h
 *
 * Description: Header file for the application
 *
 * Author: Mohamed IBRAHIM
 *
 *******************************************************************************/

#ifndef APP_H_
#define APP_H_

#include "../std_types.h"
#include "../ECUAL_layer/LED_driver/led.h"
#include "../ECUAL_layer/BUTTON_driver/button.h"
#include "../MCAL_layer/INTERRUPT_driver/interrupt.h"
#include "../MCAL_layer/TIMER0/timer0.h"


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description :
 * This function is responsible for initializing the peripherals used
 */
void APP_init(void);

/*
 * Description : This Function gets temperature sensor reading, prints it on the LCD, and controls the
 * 				 motor state based on the temperature value.
 */
void APP_start(void);

void exti0_isr(void);
void cars_yellow_blink_isr(void);
void delay_isr(void);
void two_yellows_blink_isr(void);


#endif /* APP_H_ */
