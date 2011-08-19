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

#ifndef PORTMACRO_H
#define PORTMACRO_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------
 * Port specific definitions.  
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#define portCHAR		char
#define portFLOAT		float
#define portDOUBLE		double
#define portLONG		long
#define portSHORT		short
#define portSTACK_TYPE	unsigned portLONG
#define portBASE_TYPE	portLONG

#if( configUSE_16_BIT_TICKS == 1 )
	typedef unsigned portSHORT portTickType;
	#define portMAX_DELAY ( portTickType ) 0xffff
#else
	typedef unsigned portLONG portTickType;
	#define portMAX_DELAY ( portTickType ) 0xffffffff
#endif
/*-----------------------------------------------------------*/	

/* Interrupt control macros. */
#define portDISABLE_INTERRUPTS() { asm volatile ("msrclr r0, 2;"); }
#define portENABLE_INTERRUPTS() { asm volatile ("msrset r0, 2;"); }
/*-----------------------------------------------------------*/

/* Critical section macros. */
void vPortEnterCritical( void );
void vPortExitCritical( void );
//#define portENTER_CRITICAL()	vPortEnterCritical()
//#define portEXIT_CRITICAL()	vPortExitCritical()
#define portENTER_CRITICAL()		{														\
										extern unsigned portBASE_TYPE uxCriticalNesting;	\
										portDISABLE_INTERRUPTS();					\
										uxCriticalNesting++;								\
									}

#define portEXIT_CRITICAL()			{														\
										extern unsigned portBASE_TYPE uxCriticalNesting;	\
										uxCriticalNesting--;								\
										if( uxCriticalNesting == 0 )			\
										{													\
											portENABLE_INTERRUPTS();						\
										}													\
									}

/*-----------------------------------------------------------*/

/* Task utilities. */
void vPortYield( void );
#define portYIELD() vPortYield()

void vTaskSwitchContext();
#define portYIELD_FROM_ISR() vTaskSwitchContext()
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portBYTE_ALIGNMENT			4
#define portSTACK_GROWTH			( -1 )
#define portTICK_RATE_MS			( ( portTickType ) 1000 / configTICK_RATE_HZ )		
#define portNOP()					asm volatile ( "XOR	r0, r0, r0" )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) void vFunction( void *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) void vFunction( void *pvParameters )

#ifdef __cplusplus
}
#endif

#endif /* PORTMACRO_H */

