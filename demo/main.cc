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

#include "FreeRTOSConfig.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

#include <stdio.h>

/* Tasks functions Prototype */
void vTestTask1(void *pvParameters);
void vTestTask2(void *pvParameters);
void vTestTask3(void *pvParameters);

int main(void) {
	int TaskNumber = 0;

	/* When re-starting a debug session (rather than cold booting) we want
	 to ensure the installed interrupt handlers do not execute until after the
	 scheduler has been started. */
	portDISABLE_INTERRUPTS();

	puts("FreeRTOS");

	/* Creating some tasks for the scheduler to run */
	xTaskCreate( vTestTask1, /* Pointer to the function that implements the task */
			(const signed char*)"T0", /* Text name for the task. This is to facilitate debugging only */
			1000, /* Stack depth - the size is large because printf is used for the program testing */
			NULL, /* Task parameter is not used */
			1 , /* This task will run at priority 1 */
			NULL); /* Task handle is not used */

	xTaskCreate( vTestTask2, (const signed char*)"T1", 1000, NULL,1 , NULL );
	xTaskCreate( vTestTask3, (const signed char*)"T2", 1000, NULL,1 , NULL );

	/* Get the number of the tasks created from the task queue */
	TaskNumber = uxTaskGetNumberOfTasks();

	puts(tskKERNEL_VERSION_NUMBER);

	/* Call this function to start the scheduler */
	vTaskStartScheduler();

	/* The program should not reach this point since the scheduler is running! */
	return -1;
}

void vTestTask1(void *pvParameters) {
	while (1) {
		/* Get the timer value everytime this task is executed*/
		//unsigned int value1 = getTimer0();

		/* A string that the task is displaying everytime it runs */
		portENTER_CRITICAL();
		puts("Task 1");
		portEXIT_CRITICAL();

		/* Uncomment this when you use cooperative multitasking so the currently running task gives up the processor resources */
		//taskYIELD();
	}
}

void vTestTask2(void *pvParameters) {
	int *TMR0 = (int *) 0xFFFFFFF0;
	while (1) {
		portENTER_CRITICAL();
		iprintf("Task 2 %X\n", *TMR0);
		portEXIT_CRITICAL();
	}
}

void vTestTask3(void *pvParameters) {
	int tmp;
	while (1) {
		asm volatile ("mfs	%0, rmsr;":"=r"(tmp));
		portENTER_CRITICAL();
		iprintf("Task 3 %X\n", tmp);
		portEXIT_CRITICAL();
	}
}

