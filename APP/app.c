/******************************************************************************
 *
 * Module: APP
 *
 * File Name: app.c
 *
 * Description: Source file for the application
 *
 * Author: Mohamed IBRAHIM
 *
 *******************************************************************************/


#include "app.h"
#include <util/delay.h>

static void NormalMode_delay_5s(void);
static void PedestrianMode_delay_5s(void);
static void NormalMode_carsYellowBlink_5s(void);
static void PedestrianMode_twoYellowBlink_5s(void);

volatile uint8 interrupt_on_red = 0; /* flag to mark if an interrupt happened during cars red is on */
volatile uint8 interrupt_flag = 0;	 /* flag to mark that pedestrian button has been pressed */
volatile uint8 pedestrian_request_waiting = 0;	/* flag to mark that there is a pedestrian request waiting to be handled */

volatile uint16 ticks = 0;	/* used to calculate delays */

/* CARS' TRAFFIC LIGHT lEDs */
led_t cars_green_led  = {.port_id = PORTA_ID, .pin_id = PIN_5};
led_t cars_yellow_led = {.port_id = PORTA_ID, .pin_id = PIN_6};
led_t cars_red_led    = {.port_id = PORTA_ID, .pin_id = PIN_7};

/* PEDESTRIANS' TRAFFIC LIGHT lEDs */
led_t pedestrian_green_led  = {.port_id = PORTB_ID, .pin_id = PIN_3};
led_t pedestrian_yellow_led = {.port_id = PORTB_ID, .pin_id = PIN_4};
led_t pedestrian_red_led    = {.port_id = PORTB_ID, .pin_id = PIN_5};



/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * This function is responsible for initializing the peripherals used
 */
void APP_init(void)
{
	/* initialize cars LEDs */
	LED_init(&cars_green_led);
	LED_init(&cars_yellow_led);
	LED_init(&cars_red_led);

	/* initialize pedestrians LEDs */
	LED_init(&pedestrian_green_led);
	LED_init(&pedestrian_yellow_led);
	LED_init(&pedestrian_red_led);

	/* configure EXTI0 */
	/* Setting interrupt pin as input, with a pull-up resistor an active-low button */
	button_t pedestrian_btn = {.button_active_t = BUTTON_ACTIVE_LOW, .port_id = PORTD_ID, .pin_id = PIN_2};
	BUTTON_init(&pedestrian_btn);

	/* Set interrupt trigger to rising edge, to handle long press situations */
	INTERRUPT_EXTI0_setTrigger(RISING_EGDE);

	/* enable both global interrupt and extrnal interrupt 0 */
	INTERRUPT_globalInterruptEnable();
	INTERRUPT_EXTI0_Enable();

	/* set callback function for external interrupt 0 */
	INTERRUPT_EXTI0_setCallback(exti0_isr);

	/* enable timer0 output compare match interrupt */
	INTERRUPT_TIMER0_OC_ENABLE();
}


void APP_start(void)
{
	/* NORMAL MODE */

	/* Ignore state 1 if there is ongoing interrupt request */
	if (!interrupt_flag)
	{
		/************************ FIRST state: Cars GREEN && Pedestrian RED are ON ********************/
		LED_on(&cars_green_led);
		LED_on(&pedestrian_red_led);

		/* delay for 5 seconds */
		NormalMode_delay_5s();
	}else{}
	/**********************************************************************************************/

	/* if pedestrian request was handled, clear interrupt flag */
	if (!pedestrian_request_waiting)
	{
		interrupt_flag = 0;
	}else{}


	/****************** SECOND state: Cars YELLOW BLINKS && Pedestrian RED still ON ****************/
	/* turn off previous state LEDs, and turn on second state LEDs */
	LED_off(&cars_green_led);
	LED_on(&cars_yellow_led);
	LED_on(&pedestrian_red_led);

	/* blink cars yellow LED for 5 sec */
	NormalMode_carsYellowBlink_5s();

	LED_off(&cars_yellow_led);

	/***********************************************************************************************/
	/* Ignore state 1 if there is ongoing interrupt request */
	if (!interrupt_flag)
	{
		/****************** THIRD state: Cars RED && Pedestrian GREEN are ON ****************/

		/* turn off previous state LEDs, and turn on second state LEDs */
		LED_off(&cars_yellow_led);
		LED_off(&pedestrian_red_led);
		LED_on(&cars_red_led);
		LED_on(&pedestrian_green_led);

		/* set interrupt_on_red flag */
		interrupt_on_red = 1;

		/* delay for 5 seconds */
		NormalMode_delay_5s();

		/* if not interrupted at this state, reset the flag */
		if (!interrupt_flag)
		{
			interrupt_on_red = 0;
		}else{}
	}else{}
	/************************************************************************************************/

	/* Ignore state 1 if there is ongoing interrupt request */
	if (!interrupt_flag)
	{
		/* FOURTH state: Cars YELLOW BLINKS && Pedestrian RED is ON */
		LED_off(&cars_red_led);
		LED_off(&pedestrian_green_led);

		LED_on(&cars_yellow_led);
		LED_on(&pedestrian_red_led);

		/* blink cars yellow LED for 5 sec */
		NormalMode_carsYellowBlink_5s();


		LED_off(&cars_yellow_led);
	}else{}
	/***************************************************************************************************/
	/***************************************************************************************************/

	/* if interrupt is fired "button pressed" */
	/* Pedestrian Mode */
	if (interrupt_flag)
	{
		INTERRUPT_EXTI0_Disable(); /* disable external interrupt 0, to handle multi-press situations */

		/* Check if interrupt happened when Cars green LED was on */
		if (interrupt_on_red)
		{

			/* extend that state for 5 seconds */
			PedestrianMode_delay_5s();

			/* turn of that state LEDs */
			LED_off(&cars_red_led);
			LED_off(&pedestrian_green_led);
		}

		/* if interrupt happened when Cars yellow or green was on */
		else
		{
			/* the coming state requires both yellow LEDs only to blink*/
			/* Turn off Cars green and Pedestrian red LEDs since they were on when interrupt happened */
			LED_off(&cars_green_led);
			LED_off(&pedestrian_red_led);

			/* BLINK both Cars && Pedestrian YELLOWS for 5 seconds*/
			LED_on(&cars_yellow_led);
			LED_on(&pedestrian_yellow_led);

			PedestrianMode_twoYellowBlink_5s();

			LED_off(&cars_yellow_led);
			LED_off(&pedestrian_yellow_led);

			/* then, SET cars RED && Pedestrian GREEN to ON state for 5 seconds*/
			LED_on(&cars_red_led);
			LED_on(&pedestrian_green_led);

			/* delay for 5 seconds */
			PedestrianMode_delay_5s();

			LED_off(&cars_red_led);
			LED_off(&pedestrian_green_led);
		}

		/* after above both conditions */
		/* BLINK both Cars && Pedestrian YELLOWS for 5 seconds*/
		LED_on(&cars_yellow_led);
		LED_on(&pedestrian_yellow_led);

		PedestrianMode_twoYellowBlink_5s();

		LED_off(&cars_yellow_led);
		LED_off(&pedestrian_yellow_led);

		/* then, SET Cars GREEN && pedestrian RED to ON state for 5 seconds */
		LED_on(&cars_green_led);
		LED_on(&pedestrian_red_led);

		/* delay for 5 seconds */
		PedestrianMode_delay_5s();

		LED_off(&cars_green_led);
		LED_off(&pedestrian_red_led);

		/* clear pedestrian_request_waiting flag */
		pedestrian_request_waiting = 0;

		/* Enable external interrupt 0 */
		INTERRUPT_EXTI0_Enable();
	}
}


/* ISR for external interrupt 0 */
void exti0_isr(void)
{
	/* when a pedestrian pushes the button */
	interrupt_flag = 1;
	pedestrian_request_waiting = 1;
	TIMER0_STOP();
	ticks = 0;
}

/* ISR for timer0 compare match, increments tick counter with every interrupt */
void delay_isr(void)
{
	/* increment tick counter with every interrupt */
	ticks++;
}

/* ISR for timer0 compare match, increments tick counter, toggles cars yellow with every interrupt */
void cars_yellow_blink_isr(void)
{
	ticks++;
	LED_toggle(&cars_yellow_led);
}

/* ISR for timer0 compare match, increments tick counter,
 * 								 toggles both cars yellow and pedestrian yellow LEDs with every interrupt */
void two_yellows_blink_isr(void)
{
	ticks++;
	LED_toggle(&cars_yellow_led);
	LED_toggle(&pedestrian_yellow_led);
}

static void NormalMode_delay_5s(void)
{
	/* delay 5 seconds */
	/* timer 0 can generate a max of 256 ms at a time, configure to calculate 250 ms for 20 times */
	/* increment tick counter with every 250 ms interrupt */
	INTERRUPT_TIMER0_OCF_setCallback(delay_isr);
	TIMER0_calc_ms(250);
	while(!interrupt_flag && ticks < 20);

	/* stop timer and reset ticks */
	ticks = 0;
	TIMER0_STOP();
}
static void PedestrianMode_delay_5s(void)
{
	/* delay 5 seconds */
	/* timer 0 can generate a max of 256 ms at a time, configure to calculate 250 ms for 20 times */
	/* increment tick counter with every 250 ms interrupt */
	INTERRUPT_TIMER0_OCF_setCallback(delay_isr);
	TIMER0_calc_ms(250);
	while(ticks < 20);

	/* stop timer and reset ticks */
	ticks = 0;
	TIMER0_STOP();
}

static void NormalMode_carsYellowBlink_5s(void)
{
	/* timer 0 can generate a max of 256 ms at a time, configure to calculate 250 ms for 20 times */
	/* increment tick counter with every 250 ms interrupt, toggle cars yellow led to get the blink effect */
	TIMER0_calc_ms(250);
	INTERRUPT_TIMER0_OCF_setCallback(cars_yellow_blink_isr);
	while(!interrupt_flag && ticks < 20);

	/* stop timer and reset ticks */
	ticks = 0;
	TIMER0_STOP();
}


static void PedestrianMode_twoYellowBlink_5s(void)
{

	/* delay 5 seconds */
	/* timer 0 can generate a max of 256 ms at a time, configure to calculate 250 ms for 20 times */
	/* increment tick counter with every 250 ms interrupt, toggle cars yellow led to get the blink effect */
	TIMER0_calc_ms(250);
	INTERRUPT_TIMER0_OCF_setCallback(two_yellows_blink_isr);
	while(ticks < 20);

	/* stop timer and reset ticks */
	ticks = 0;
	TIMER0_STOP();
}


