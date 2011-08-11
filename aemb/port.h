/*
 FreeRTOS AEMB2 Port
 Copyright (C) 2011 Aeste Works (M) Sdn Bhd.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see http://www.gnu.org/licenses/.

 * @file port.h
 *  Created on: Aug 11, 2011
 *      Author: Shawn Tan <shawn.tan@aeste.my>
 *
 */

#ifndef PORT_H_
#define PORT_H_

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
#define portISR_STACK_FILL_VALUE	0xAEAEAEAE

/* Counts the nesting depth of calls to portENTER_CRITICAL().  Each task
 maintains it's own count, so this variable is saved as part of the task
 context. */
unsigned portBASE_TYPE uxCriticalNesting = portINITIAL_NESTING_VALUE;

/* To limit the amount of stack required by each task, this port uses a
 separate stack for interrupts. */
unsigned long *pulISRStack;

/*-----------------------------------------------------------*/
/* TODO: Convert ASM to C later
 static inline void portSAVE_CONTEXT() {
 // Make room for the context on the stack.
 asm volatile("addik r1, r1, -132;");
 // Save r31 so it can then be used.
 asm volatile("swi r31, r1, 4;");
 // Copy the msr into r31 - this is stacked later.
 asm volatile("mfs r31, rmsr;");
 // Stack general registers.
 asm volatile("swi r30, r1, 12;"
 "swi r29, r1, 16;"
 "swi r28, r1, 20;"
 "swi r27, r1, 24;"
 "swi r26, r1, 28;"
 "swi r25, r1, 32;"
 "swi r24, r1, 36;"
 "swi r23, r1, 40;"
 "swi r22, r1, 44;"
 "swi r21, r1, 48;"
 "swi r20, r1, 52;"
 "swi r19, r1, 56;"
 "swi r18, r1, 60;"
 "swi r17, r1, 64;"
 "swi r16, r1, 68;"
 "swi r15, r1, 72;"
 "swi r13, r1, 80;"
 "swi r12, r1, 84;"
 "swi r11, r1, 88;"
 "swi r10, r1, 92;"
 "swi r9, r1, 96;"
 "swi r8, r1, 100;"
 "swi r7, r1, 104;"
 "swi r6, r1, 108;"
 "swi r5, r1, 112;"
 "swi r4, r1, 116;"
 "swi r3, r1, 120;"
 "swi r2, r1, 124;");
 // Stack the critical section nesting value.
 asm volatile("lwi r3, r0, uxCriticalNesting;"
 "swi r3, r1, 128;");
 // Save the top of stack value to the TCB.
 asm volatile("lwi r3, r0, pxCurrentTCB;"
 "sw r1, r0, r3");

 }

 inline void portRESTORE_CONTEXT() {
 // Load the top of stack value from the TCB.
 asm volatile ("lwi r3, r0, pxCurrentTCB;"
 "lw	r1, r0, r3;");
 // Restore the general registers.
 asm volatile ("lwi r31, r1, 4		;"
 "lwi r30, r1, 12		;"
 "lwi r29, r1, 16	;"
 "lwi r28, r1, 20	;"
 "lwi r27, r1, 24	;"
 "lwi r26, r1, 28	;"
 "lwi r25, r1, 32	;"
 "lwi r24, r1, 36	;"
 "lwi r23, r1, 40	;"
 "lwi r22, r1, 44	;"
 "lwi r21, r1, 48	;"
 "lwi r20, r1, 52	;"
 "lwi r19, r1, 56	;"
 "lwi r18, r1, 60	;"
 "lwi r17, r1, 64	;"
 "lwi r16, r1, 68	;"
 "lwi r15, r1, 72	;"
 "lwi r14, r1, 76	;"
 "lwi r13, r1, 80	;"
 "lwi r12, r1, 84	;"
 "lwi r11, r1, 88	;"
 "lwi r10, r1, 92	;"
 "lwi r9, r1, 96	;"
 "lwi r8, r1, 100	;"
 "lwi r7, r1, 104;"
 "lwi r6, r1, 108;"
 "lwi r5, r1, 112;"
 "lwi r4, r1, 116;"
 "lwi r2, r1, 124;");

 // Load the critical nesting value.
 asm volatile ("lwi r3, r1, 128;"
 "swi r3, r0, uxCriticalNesting;");

 // Obtain the MSR value from the stack.
 asm volatile("lwi r3, r1, 8;");

 // Are interrupts enabled in the MSR?  If so return using an return fro interrupt instruction to ensure interrupts are enabled only once the task is running again.
 asm volatile("andi r3, r3, 2;"
 "beqid r3, 36;"
 "xor r0, r0, r0;");

 // Reload the rmsr from the stack, clear the enable interrupt bit in the value before saving back to rmsr register, then return enabling interrupts as we return.
 asm volatile("lwi r3, r1, 8;"
 "andi r3, r3, ~2;"
 "mts rmsr, r3;"
 "lwi r3, r1, 120;"
 "rtid r14, 0;"
 "addik r1, r1, 132;");

 // Reload the rmsr from the stack, place it in the rmsr register, and return without enabling interrupts.
 asm volatile("lwi r3, r1, 8;"
 "mts rmsr, r3;"
 "lwi r3, r1, 120;"
 "rtsd r14, 0;"
 "addik r1, r1, 132;");

 }

 #define vStartFirstTask() {	portRESTORE_CONTEXT(); }

 void VPortYieldASM() {
 portSAVE_CONTEXT();
 // Stack msr.
 asm volatile ("swi r31, r1, 8;");
 // Modify the return address so we return to the instruction after the exception.
 asm volatile ("addi r14, r14, 8;"
 "swi r14, r1, 76;");
 // Now switch to use the ISR stack.
 asm volatile ("lwi r3, r0, pulISRStack;"
 "bralid r15, vTaskSwitchContext;"
 "add r1, r3, r0;");
 portRESTORE_CONTEXT();
 }

 void _interrupt_handler() {
 portSAVE_CONTEXT();
 // Entered via an interrupt so interrupts must be enabled in msr.
 asm volatile("ori r31, r31, 2;");
 // Stack msr.
 asm volatile("swi r31, r1, 8;");
 // Stack the return address.  As we entered via an interrupt we do not need to modify the return address prior to stacking.
 asm volatile("swi r14, r1, 76;");
 // Now switch to use the ISR stack.
 asm volatile("lwi r3, r0, pulISRStack;");
 // DELAY add r1, r3, r0
 asm volatile("bralid r15, vTaskISRHandler;"
 "add r1, r3, r0;");
 portRESTORE_CONTEXT();
 }

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

/**
 Hardware Mutex Signal.
 Unlock the hardware mutex, which is unlocked on reset.
 */
inline void _aembFreeMTX() {
	int tmp;
	asm volatile ("msrclr %0, %1":"=r"(tmp):"K"(16));
}

/**
 Hardware Mutex Wait.

 Waits until the hardware mutex is unlocked. This should be used
 as part of a larger software mutex mechanism.
 */
inline void _aembLockMTX() {
	int rmsr;
	do {
		asm volatile ("msrset %0, %1":"=r"(rmsr):"K"(16));
	} while (rmsr & 16);
}

/**
 Checks to see if currently executing Thread 1
 @return true if is Thread 1
 */

inline int aembIsThread1() {
	int rmsr;
	asm volatile ("mfs %0, rmsr":"=r"(rmsr));
	return ((rmsr & (1 << 29)));
}

/**
 Checks to see if currently executing Thread 0
 @return true if is Thread 0
 */

inline int aembIsThread0() {
	int rmsr;
	asm volatile ("mfs %0, rmsr":"=r"(rmsr));
	return ((!(rmsr & (1 << 29))));
}

void _loop() {
	while (1)
		;
}

void _program_init() {
	_aembLockMTX(); // enter critical section

	// split and shift the stack for thread 1
	if (aembIsThread1()) // main thread
	{
		_aembFreeMTX(); // exit critical section
		while (1)
			asm volatile ("nop");
		// lock thread
	}

	_aembFreeMTX(); // exit critical section
}

#endif // PORT_H_
