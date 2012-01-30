/*
 AEMB2 FREERTOS PORT
 Copyright (C) 2011 AESTE WORKS (M) SDN BHD.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PORT_H_
#define PORT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "task.h"

/* Tasks are started with interrupts enabled. */
#define portINITIAL_MSR_STATE		( ( portSTACK_TYPE ) 0x02 )

/* Tasks are started with a critical section nesting of 0 - however prior
 to the scheduler being commenced we don't want the critical nesting level
 to reach zero, so it is initialised to a high value. */
#define portINITIAL_NESTING_VALUE	( 0xff )

/* Our hardware setup only uses one counter. */
#define portCOUNTER_0 				0

/* The stack used by the ISR is filled with a known value to assist in
 debugging. */
#define portISR_STACK_FILL_VALUE	0xDEADC0DE

/* Counts the nesting depth of calls to portENTER_CRITICAL().  Each task
 maintains it's own count, so this variable is saved as part of the task
 context. */
unsigned portBASE_TYPE uxCriticalNesting = portINITIAL_NESTING_VALUE;

/* To limit the amount of stack required by each task, this port uses a
 separate stack for interrupts. */
unsigned long *pulISRStack;

/*-----------------------------------------------------------*/

inline void outbyte(char c) {
	volatile char * OUTC = (char *) 0xFFFFFFC0;
	*OUTC = c;
}

inline char inbyte() {
	return 0;
}

inline int getTimer0() {
	int *TMR0 = (int *) 0xFFFFFFF0;
	return *TMR0;
}

inline int setTimer0(int timer) {
	volatile int *TMR0 = (int *) 0xFFFFFFF0;
	*TMR0 = timer;
}

/*-----------------------------------------------------------*/

void _program_init() {
	int tmp;
	asm volatile ("msrset %0, %1;"
			"andi %0, %0, %1;"
			"bnei %0, 0;"
			"msrclr r0, %1;"
			:"=r"(tmp)
			:"K"(16));
}

#ifdef __cplusplus
}
#endif

#endif // PORT_H_
