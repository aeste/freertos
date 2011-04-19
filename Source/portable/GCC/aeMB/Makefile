# headers include


XILFLAGS="-mtune=v5.00 -mxl-soft-div -msoft-float -mxl-barrel-shift -mno-xl-soft-mul"


compile: main.o list.o queue.o tasks.o port.o portasm.o heap_3.o
	mb-gcc *.o -O2

main.o: main.c ../../../../Source/include/FreeRTOS.h 
	mb-gcc $(XILFLAGS) -c main.c -O2


list.o: ../../../../Source/list.c ../../../../Source/include/FreeRTOS.h ../../../../Source/include/list.h
	mb-gcc $(XILFLAGS) -c ../../../../Source/list.c -O2


queue.o: ../../../../Source/queue.c ../../../../Source/include/FreeRTOS.h ../../../../Source/include/task.h ../../../../Source/include/croutine.h
	mb-gcc $(XILFLAGS) -c ../../../../Source/queue.c -O2

tasks.o: ../../../../Source/tasks.c ../../../../Source/include/FreeRTOS.h ../../../../Source/include/task.h ../../../../Source/include/StackMacros.h  
	mb-gcc $(XILFLAGS) -c ../../../../Source/tasks.c -O2
	

port.o: port.c ../../../../Source/include/FreeRTOS.h ../../../../Source/include/task.h 
	mb-gcc $(XILFLAGS) -c port.c -O2


portasm.o: portasm.s 
	mb-gcc $(XILFLAGS) -c portasm.s -O2


heap_3.o: ../../../../Source/portable/MemMang/heap_3.c ../../../../Source/include/FreeRTOS.h ../../../../Source/include/task.h
	mb-gcc $(XILFLAGS) -c ../../../../Source/portable/MemMang/heap_3.c -O2


