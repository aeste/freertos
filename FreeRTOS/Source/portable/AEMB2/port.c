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

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the MicroBlaze port.
 *----------------------------------------------------------*/

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Standard includes. */
#include "port.h"

/* Hardware includes. */

/*
 * Sets up the periodic ISR used for the RTOS tick.  This uses timer 0, but
 * could have alternatively used the watchdog timer or timer 1.
 */
static void prvSetupTimerInterrupt(void);
/*-----------------------------------------------------------*/

/* 
 * Initialise the stack of a task to look exactly as if a call to 
 * portSAVE_CONTEXT had been made.
 * 
 * See the header file portable.h.
 */
portSTACK_TYPE *pxPortInitialiseStack(portSTACK_TYPE *pxTopOfStack,
		pdTASK_CODE pxCode, void *pvParameters) {
	extern void *_SDA2_BASE_, *_SDA_BASE_;
	const unsigned long ulR2 = (unsigned long) &_SDA2_BASE_;
	const unsigned long ulR13 = (unsigned long) &_SDA_BASE_;

	/* Place a few bytes of known values on the bottom of the stack. 
	 This is essential for the Microblaze port and these lines must
	 not be omitted.  The parameter value will overwrite the
	 0x22222222 value during the function prologue. */
	*pxTopOfStack = (portSTACK_TYPE ) 0x11111111;
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x22222222;
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x33333333;
	pxTopOfStack--;

	/* First stack an initial value for the critical section nesting.  This
	 is initialised to zero as tasks are started with interrupts enabled. */
	*pxTopOfStack = (portSTACK_TYPE ) 0x00; /* R0. */

	/* Place an initial value for all the general purpose registers. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) ulR2; /* R2 - small data area. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x03; /* R3. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x04; /* R4. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) pvParameters;/* R5 contains the function call parameters. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x06; /* R6. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x07; /* R7. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x08; /* R8. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x09; /* R9. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x0a; /* R10. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x0b; /* R11. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x0c; /* R12. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) ulR13; /* R13 - small data read write area. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) pxCode; /* R14. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x0f; /* R15. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x10; /* R16. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x11; /* R17. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x12; /* R18. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x13; /* R19. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x14; /* R20. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x15; /* R21. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x16; /* R22. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x17; /* R23. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x18; /* R24. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x19; /* R25. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x1a; /* R26. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x1b; /* R27. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x1c; /* R28. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x1d; /* R29. */
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE ) 0x1e; /* R30. */
	pxTopOfStack--;

	/* The MSR is stacked between R30 and R31. */
	*pxTopOfStack = portINITIAL_MSR_STATE;
	pxTopOfStack--;

	*pxTopOfStack = (portSTACK_TYPE ) 0x1f; /* R31. */
	pxTopOfStack--;

	/* Return a pointer to the top of the stack we have generated so this can
	 be stored in the task control block for the task. */
	return pxTopOfStack;
}
/*-----------------------------------------------------------*/

portBASE_TYPE xPortStartScheduler(void) {
	extern void ( _interrupt_Handler)(void);
	extern void ( vStartFirstTask)(void);

	/* Setup the hardware to generate the tick.  Interrupts are disabled when
	 this function is called. */
	prvSetupTimerInterrupt();

	/* Allocate the stack to be used by the interrupt handler. */
	pulISRStack = (unsigned long *) pvPortMalloc(configMINIMAL_STACK_SIZE
			* sizeof(portSTACK_TYPE ));

	/* Restore the context of the first task that is going to run. */
	if (pulISRStack != NULL) {
		/* Fill the ISR stack with a known value to facilitate debugging. */
		memset(pulISRStack, portISR_STACK_FILL_VALUE, configMINIMAL_STACK_SIZE
				* sizeof(portSTACK_TYPE ));
		pulISRStack += (configMINIMAL_STACK_SIZE - 1);

		/* Kick off the first task. */
		vStartFirstTask();
	}

	/* Should not get here as the tasks are now running! */
	return pdFALSE;
}
/*-----------------------------------------------------------*/

void vPortEndScheduler(void) {
	/* Not implemented. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch called by portYIELD or taskYIELD.  
 */
void vPortYield(void) {
	extern void VPortYieldASM(void);

	/* Perform the context switch in a critical section to assure it is
	 not interrupted by the tick ISR.  It is not a problem to do this as
	 each task maintains it's own interrupt status. */
	portENTER_CRITICAL();

	/* Jump directly to the yield function to ensure there is no
	 compiler generated prologue code. */
	asm volatile (
			"bralid r14, VPortYieldASM;"
			"xor r0, r0, r0;"
	);
	portEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.   
 */
static void prvSetupTimerInterrupt(void) {

	/* FIXME: Replace Timer/Interrupt initialisation code. */
	setTimer0(0);

}
/*-----------------------------------------------------------*/

/* 
 * Handler for the timer interrupt.
 */
void vTickISR(void *pvBaseAddress) {

	/* Increment the RTOS tick - this might cause a task to unblock. */
	vTaskIncrementTick();

	/* Clear the timer interrupt */
	volatile *XACK = 0xFFFFFFE0;
	*XACK = -1;

	/* If we are using the preemptive scheduler then we also need to determine
	 if this tick should cause a context switch. */
#if configUSE_PREEMPTION == 1
	vTaskSwitchContext();
#endif
}

/*-----------------------------------------------------------*/

/*
 * The interrupt handler placed in the interrupt vector when the scheduler is
 * started.  The task context has already been saved when this is called.
 * This handler determines the interrupt source and calls the relevant
 * peripheral handler.
 */
void vTaskISRHandler(void) {
	vTickISR(NULL);
}

/*-----------------------------------------------------------*/
