# headers include


XILFLAGS="-mtune=v5.00 -mxl-soft-div -msoft-float -mxl-barrel-shift -mno-xl-soft-mul"


compile: main.o list.o queue.o tasks.o port.o portasm.o heap_1.o
	mb-gcc *.o

main.o: main.c ../../../../Source/include/FreeRTOS.h 
	mb-gcc $(XILFLAGS) -c main.c 


list.o: ../../../../Source/list.c ../../../../Source/include/FreeRTOS.h ../../../../Source/include/list.h
	mb-gcc $(XILFLAGS) -c ../../../../Source/list.c


queue.o: ../../../../Source/queue.c ../../../../Source/include/FreeRTOS.h ../../../../Source/include/task.h ../../../../Source/include/croutine.h
	mb-gcc $(XILFLAGS) -c ../../../../Source/queue.c

tasks.o: ../../../../Source/tasks.c ../../../../Source/include/FreeRTOS.h ../../../../Source/include/task.h ../../../../Source/include/StackMacros.h  
	mb-gcc $(XILFLAGS) -c ../../../../Source/tasks.c
	

port.o: port.c ../../../../Source/include/FreeRTOS.h ../../../../Source/include/task.h 
	mb-gcc $(XILFLAGS) -c port.c


portasm.o: portasm.s 
	mb-gcc $(XILFLAGS) -c portasm.s


heap_1.o: ../../../../Source/portable/MemMang/heap_1.c ../../../../Source/include/FreeRTOS.h ../../../../Source/include/task.h
	mb-gcc $(XILFLAGS) -c ../../../../Source/portable/MemMang/heap_1.c


