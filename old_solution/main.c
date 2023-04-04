/*
 * On-demand Traffic light control.c
 *
 * Created: 08/01/2023 11:14:39 م
 * Author : khater
 */ 


#include "APPLICATION/app.h"



int main(void)
{
	//DIO_init_test();
	//DIO_write_test();
	//DIO_toggle_test();
	//DIO_read_test();
	
	//EXT_INT0_triggerControl_test();
	//EXT_INT1_triggerControl_test();
	//EXT_INT2_triggerControl_test();
	
	//LED_init_test();
	//check_initilization_test();
	//LED_on_test();
	//LED_off_test();
	//LED_toggle_test();
	//LED_read_state_test();
	
	//blink_two_yellows_test();
	//LED_blink_interruptCheck_test();
	//leds_on_temporary_interruptCheck_test();
	
	 //BUTTON_init_test();
	// BUTTON_read_test();
	
	app_init();
	
    while (1) 
    {
		
		normalMode();
    }
}

