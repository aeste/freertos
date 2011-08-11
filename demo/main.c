/*
    FreeRTOS V6.1.1 - Copyright (C) 2011 Real Time Engineers Ltd.

    ***************************************************************************
    *                                                                         *
    * If you are:                                                             *
    *                                                                         *
    *    + New to FreeRTOS,                                                   *
    *    + Wanting to learn FreeRTOS or multitasking in general quickly       *
    *    + Looking for basic training,                                        *
    *    + Wanting to improve your FreeRTOS skills and productivity           *
    *                                                                         *
    * then take a look at the FreeRTOS books - available as PDF or paperback  *
    *                                                                         *
    *        "Using the FreeRTOS Real Time Kernel - a Practical Guide"        *
    *                  http://www.FreeRTOS.org/Documentation                  *
    *                                                                         *
    * A pdf reference manual is also available.  Both are usually delivered   *
    * to your inbox within 20 minutes to two hours when purchased between 8am *
    * and 8pm GMT (although please allow up to 24 hours in case of            *
    * exceptional circumstances).  Thank you for your support!                *
    *                                                                         *
    ***************************************************************************

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    ***NOTE*** The exception to the GPL is included to allow you to distribute
    a combined work that includes FreeRTOS without being obliged to provide the
    source code for proprietary components outside of the FreeRTOS kernel.
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public 
    License and the FreeRTOS license exception along with FreeRTOS; if not it 
    can be viewed here: http://www.freertos.org/a00114.html and also obtained 
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the standard demo application tasks.
 *
 * In addition to the standard tasks, main() creates two "Register Check" 
 * tasks.  These tasks write known values into every general purpose register,
 * then check each register to ensure it still contains the expected (written)
 * value.  The register check tasks operate at the idle priority so will get
 * repeatedly preempted.  A register being found to contain an incorrect value
 * following such a preemption would be indicative of an error in the context
 * switch mechanism.
 * 
 * Main.c also creates a task called "Check".  This only executes every three 
 * seconds but has the highest priority so is guaranteed to get processor time.  
 * Its main function is to check that all the other tasks are still operational.
 * Each task (other than the "flash" tasks) maintains a unique count that is 
 * incremented each time the task successfully completes its function.  Should 
 * any error occur within such a task the count is permanently halted.  The 
 * check task inspects the count of each task to ensure it has changed since
 * the last time the check task executed.  If all the count variables have 
 * changed all the tasks are still executing error free, and the check task
 * toggles the onboard LED.  Should any task contain an error at any time 
 * the LED toggle rate will change from 3 seconds to 500ms.
 *
 */

#include "FreeRTOSConfig.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

#include <stdlib.h>
#include <stdio.h>

// Enable global interrupts
inline int aembEnableInterrupts()
{
	int msr;
    asm volatile ("msrset %0, %1":"=r"(msr):"K"(1<<1));
    return msr;
}

// Disable global interrupts *
inline int aembDisableInterrupts()
{
    int msr;
    asm volatile ("msrclr %0, %1":"=r"(msr):"K"(1<<1));
    return msr;
}

/* Tasks functions Prototype */
void vTestTask1( void *pvParameters );
void vTestTask2( void *pvParameters );
void vTestTask3( void *pvParameters );
void vTestTask4( void *pvParameters );

int main (void) 
{
int TaskNumber = 0;

	/* When re-starting a debug session (rather than cold booting) we want
	to ensure the installed interrupt handlers do not execute until after the
	scheduler has been started. */
	portDISABLE_INTERRUPTS();

	/* Creating some tasks for the scheduler to run */
	xTaskCreate( vTestTask1, /* Pointer to the function that implements the task */
			"T1",	 /* Text name for the task. This is to facilitate debugging only */
			1000,	 /* Stack depth - the size is large because printf is used for the program testing */
			NULL,	 /* Task parameter is not used */
			  1 ,	 /* This task will run at priority 1 */
			NULL);	 /* Task handle is not used */

	xTaskCreate( vTestTask2, "T2",   1000, NULL,1 , NULL );
	xTaskCreate( vTestTask3, "T3",   1000, NULL,1 , NULL );
	xTaskCreate( vTestTask4, "T4",   1000, NULL,1 , NULL );
	
	/* Get the number of the tasks created from the task queue */
	TaskNumber = uxTaskGetNumberOfTasks();

	printf("\n\nCommencing The Scheduler With %d Tasks... \n\n", TaskNumber);
	
	/* Call this function to start the scheduler */
	vTaskStartScheduler();

	/* The program should not reach this point since the scheduler is running! */
   	return 0;
}


void vTestTask1( void *pvParameters )
{
    for (;;)
	{	
		/* Get the timer value everytime this task is executed*/
		unsigned int value1 = getTimer0();

		/* A string that the task is displaying everytime it runs */
		printf("Task 1 running %u\n",value1);
	
		/* Uncomment this when you use cooperative multitasking so the currently running task gives up the processor resources */
    		//taskYIELD();
    	}
}

void vTestTask2( void *pvParameters )
{
    for (;;)
	{	unsigned int value2 = getTimer0();
		printf("Task 2 running %u\n",value2);

		//taskYIELD();
	}
}


void vTestTask3( void *pvParameters )
{
    for (;;)
	{	unsigned int value3 = getTimer0();
		printf("Task 3 running %u\n",value3);

    		//taskYIELD();
    	}
}

void vTestTask4( void *pvParameters )
{
    for (;;)
	{	unsigned int value4 = getTimer0();
		printf("Task 4 running %u\n",value4);

    		//taskYIELD();
    	}
}

