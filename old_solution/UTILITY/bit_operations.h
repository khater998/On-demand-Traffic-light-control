/*
 * bit_operations.h
 *
 * Created: 11/01/2023 01:43:27 م
 *  Author: khater
 */ 


#ifndef BIT_OPERATIONS_H_
#define BIT_OPERATIONS_H_


// BIT MANIPULATION
#define SET_BIT(PORT,PIN)		(PORT) |=  (1<<PIN)
#define CLR_BIT(PORT,PIN)		(PORT) &= ~(1<<PIN)
#define TOGGLE_BIT(PORT,PIN)	(PORT) ^=  (1<<PIN)
#define READ_BIT(PORT,PIN)		((PORT) & (1<<PIN)) >>PIN

#endif /* BIT_OPERATIONS_H_ */