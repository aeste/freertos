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

#include <stdlib.h>
#include <stdio.h>

/* Core includes */
#include "aeinclude/core.hh"
#include "aeinclude/simboard.hh"

/* Scheduler includes. */
#include "../../../../Source/include/FreeRTOS.h"
#include "../../../../Source/include/task.h"


/*
 * Perform any necessary hardware configuration.
 */
static void prvSetupHardware( void );

/* Set to pdFAIL should an error be discovered in the register test tasks. *
static unsigned long ulRegisterTestStatus = pdPASS;
const unsigned long *pulStatusAddr = &ulRegisterTestStatus;

/*-----------------------------------------------------------*/

/*
 * Create all the demo tasks - then start the scheduler.
 */
void vTestTask( void *pvParameters )
{
        
	printf("\n\t\t---Test Task is running---\n\n");

   // Because FreeRTOS tasks are implemented as an infinite loop	
	while(1);
}



int main (void) 
{

portBASE_TYPE FIReturn;
	/* When re-starting a debug session (rather than cold booting) we want
	to ensure the installed interrupt handlers do not execute until after the
	scheduler has been started. */
	portDISABLE_INTERRUPTS();

	FIReturn = xTaskCreate( vTestTask, "T0",   1000, NULL,1 , NULL );
	
	if( FIReturn == pdPASS )
	{
	
		printf("\n\n\t --- Stack Memory Allocation passed! ---\n\n");
	}
	else {
		printf("\n\n ------- Stack Memory Allocation failed! --------\n\n");
	}
	
	vTaskStartScheduler();


   	return 0;
}


static void prvSetupHardware( void )
{
	
}

