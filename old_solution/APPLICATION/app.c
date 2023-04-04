/*
 * app.c
 *
 * Created: 09/01/2023 12:22:33 ص
 *  Author: khater
 */ 

#include "app.h"

uint8_t interrupt_triggered = 0;
uint8_t cars_red_flag = 0;

/* CARS' TRAFFIC LIGHT lEDs */
led_t cars_green_led  = {.portNumber = PORT_A, .pinNumber = 5};
led_t cars_yellow_led = {.portNumber = PORT_A, .pinNumber = 6};
led_t cars_red_led    = {.portNumber = PORT_A, .pinNumber = 7};

/* PEDESTRIANS' TRAFFIC LIGHT lEDs */
led_t pedestrian_green_led  = {.portNumber = PORT_B, .pinNumber = 3};
led_t pedestrian_yellow_led = {.portNumber = PORT_B, .pinNumber = 4};
led_t pedestrian_red_led    = {.portNumber = PORT_B, .pinNumber = 5};

void app_init() 
{
	/* Initialize the button and LEDs */
	button_t btn = { .portNumber = PORT_D, .pinNumber = 2 };
	BUTTON_init(&btn);
	
	LED_init(&cars_green_led);
	LED_init(&cars_yellow_led);
	LED_init(&cars_red_led);

	LED_init(&pedestrian_green_led);
	LED_init(&pedestrian_yellow_led);
	LED_init(&pedestrian_red_led);
	
	/* Enable Global interrupt and External interrupt 0  */
	GLOBAL_INTERRUPT_ENABLE();
	EXT_INT0_triggerControl(FALLING_EDGE);
	EXT_INT0_ENABLE();
}


void normalMode()
{
	
	/* FIRST state: Cars GREEN && Pedestrian RED are ON*/
	if (interrupt_triggered == 0 )
	{
		leds_on_temporary_interruptCheck(&cars_green_led,&pedestrian_red_led, 5);
	}
	
	/* WHERE PEDESTRIAN MODE ENDS */ 
	interrupt_triggered = 0;
	
	/* SECOND STATE: Cars YELLOW BLINKS && Pedestrian RED still ON*/
	LED_on(&pedestrian_red_led);
	LED_blink_interruptCheck(&cars_yellow_led,5);			
	LED_off(&pedestrian_red_led);

	if (interrupt_triggered == 0) /* if interrupt happened in the above state, skip to the state where pedestrian mode ends */
	{
		/* THIRD state: Cars RED && Pedestrian GREEN are ON */
		cars_red_flag = 1;
		leds_on_temporary_interruptCheck(&cars_red_led,&pedestrian_green_led, 5);				
		cars_red_flag = 0;
		
		/* FOURTH state: Cars YELLOW BLINKS && Pedestrian RED is ON */ 
		if (interrupt_triggered == 0)
		{
		LED_on(&pedestrian_red_led);								
		LED_blink_interruptCheck(&cars_yellow_led,5);
		}
	}	
}

void pedesterianMode()
{
	/* if interrupt happens when Cars RED is ON */
	if (cars_red_flag == 1)
	{	
		_delay_ms(5000);
		LED_off(&cars_red_led);
		LED_off(&pedestrian_green_led);
	}
	else /* interrupt happens when Cars GREEN or YELLOW are ON*/
	{
		LED_off(&cars_green_led);
		LED_off(&pedestrian_red_led);
			
		/* BLINK both Cars && Pedestrian YELLOWS for 5 seconds*/
		blink_two_yellows(&cars_yellow_led,&pedestrian_yellow_led,5);
		
		/* then, SET cars RED && Pedestrian GREEN to ON state for 5 seconds*/
		LED_on(&pedestrian_green_led);
		LED_on(&cars_red_led);
		_delay_ms(5000);
		LED_off(&pedestrian_green_led);
		LED_off(&cars_red_led);
	}
	
	/* for both conditions */ 
	/* BLINK both Cars && Pedestrian YELLOWS for 5 seconds */
	blink_two_yellows(&cars_yellow_led,&pedestrian_yellow_led,5);
	
	/* then, SET Cars GREEN && pedestrian RED to ON state for 5 seconds */
	LED_on(&pedestrian_red_led);
	LED_on(&cars_green_led);
	_delay_ms(5000);
	LED_off(&pedestrian_red_led);
	LED_off(&cars_green_led);	
}



ISR(INT0_vect)
{
	/* Disable interrupt 0 till ISR is executed */
	pedesterianMode();
	interrupt_triggered = 1;
}
