compile: main.o list.o queue.o tasks.o port.o portasm.o heap_1.o microblaze_disable_interrupts.o microblaze_enable_interrupts.o
	mb-gcc *.o

main.o: main.c ../../../../Source/include/FreeRTOS.h ../../../../Source/include/task.h xinclude/xintc.h
	mb-gcc -c main.c 


list.o: ../../../../Source/list.c ../../../../Source/include/FreeRTOS.h ../../../../Source/include/list.h
	mb-gcc -c ../../../../Source/list.c


queue.o: ../../../../Source/queue.c ../../../../Source/include/FreeRTOS.h ../../../../Source/include/task.h ../../../../Source/include/croutine.h
	mb-gcc -c ../../../../Source/queue.c

tasks.o: ../../../../Source/tasks.c ../../../../Source/include/FreeRTOS.h ../../../../Source/include/task.h ../../../../Source/include/StackMacros.h ../../../../Source/portable/GCC/MicroBlaze/xinclude/xintc_l.h  
	mb-gcc -c ../../../../Source/tasks.c
	

port.o: port.c ../../../../Source/include/FreeRTOS.h ../../../../Source/include/task.h xinclude/xparameters.h xinclude/xintc.h xinclude/xintc_i.h xinclude/xtmrctr.h
	mb-gcc -c port.c


portasm.o: portasm.s 
	mb-gcc -c portasm.s


heap_1.o: ../../../../Source/portable/MemMang/heap_1.c ../../../../Source/include/FreeRTOS.h ../../../../Source/include/task.h
	mb-gcc -c ../../../../Source/portable/MemMang/heap_1.c


microblaze_disable_interrupts.o: microblaze_disable_interrupts.s
	mb-gcc -c microblaze_disable_interrupts.s


microblaze_enable_interrupts.o: microblaze_enable_interrupts.s
	mb-gcc -c microblaze_enable_interrupts.s
