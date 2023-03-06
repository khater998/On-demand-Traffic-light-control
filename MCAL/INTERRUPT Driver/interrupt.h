/*
 * interrupt.h
 *
 * Created: 09/01/2023 07:56:33 م
 *  Author: khater
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_



#include "../DIO Driver/dio.h"
#include "../../UTILITY/registers.h"
#include "../../UTILITY/STD_types.h"
#include "../../UTILITY/bit_operations.h"

/* Define trigger conditions for interrupt 0 && interrupt 1 */
typedef enum triggerControl
{
	LOW_LVL,
	ANY_LOGICAL,
	FALLING_EDGE,
	RISING_EDGE
}triggerControl_t;

/* Define trigger conditions for interrupt 2 */
typedef enum triggerControl_INT2
{
	FALLING_EDGE_INT2,
	RISING_EDGE_INT2
}triggerControl_INT2_t;

typedef enum
{
	INTERRUPT_ok,
	undefined_trigger_condition
	}EN_INTERRUPT_error;


/* CONTROLLING GLOBAL INTERRUPT */
#define GLOBAL_INTERRUPT_ENABLE()		SET_BIT(SREG,7)             
#define GLOBAL_INTERRUPT_DISABLE()		CLR_BIT(SREG,7)

/* CONTROLLING EXTERNAL INTERRUPT 0 */
#define EXT_INT0_ENABLE()				SET_BIT(GICR,6)
#define EXT_INT0_DISABLE()				CLR_BIT(GICR,6)

/* CONTROLLING EXTERNAL INTERRUPT 1 */
#define EXT_INT1_ENABLE()				SET_BIT(GICR,7)
#define EXT_INT1_DISABLE()				CLR_BIT(GICR,7)

/* CONTROLLING EXTERNAL INTERRUPT 2 */
#define EXT_INT2_ENABLE()				SET_BIT(GICR,5)
#define EXT_INT2_DISABLE()				CLR_BIT(GICR,5)



EN_INTERRUPT_error EXT_INT0_triggerControl(triggerControl_t trigger_condition);				/* set trigger condition for interrupt 0 */
EN_INTERRUPT_error EXT_INT1_triggerControl(triggerControl_t trigger_condition);				/* set trigger condition for interrupt 1 */
EN_INTERRUPT_error EXT_INT2_triggerControl(triggerControl_INT2_t trigger_condition);		/* set trigger condition for interrupt 2 */

void EXT_INT0_triggerControl_test();
void EXT_INT1_triggerControl_test();
void EXT_INT2_triggerControl_test();

#endif /* INTERRUPT_H_ */