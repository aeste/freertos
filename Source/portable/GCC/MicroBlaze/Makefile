# .......... headers included in the project...........
 
FreeRTOS = ../../../../Source/include/FreeRTOS.h
task = ../../../../Source/include/task.h
list = ../../../../Source/include/list.h
croutine = ../../../../Source/include/croutine.h
StackMacros = ../../../../Source/include/StackMacros.h
xintc = xinclude/xintc.h
xintc_l = xinclude/xintc_l.h
xintc_i = xinclude/xintc_i.h
xparameters = xinclude/xparameters.h
xtmrctr = xinclude/xtmrctr.h
# .....................................................

compile: main.o list.o queue.o tasks.o port.o portasm.o heap_1.o microblaze_disable_interrupts.o microblaze_enable_interrupts.o
	mb-gcc *.o

main.o: main.c $(FreeRTOS) $(task) $(xintc)
	mb-gcc -c main.c DEPS = hellomake.h


list.o: ../../../../Source/list.c $(FreeRTOS) $(list)
	mb-gcc -c ../../../../Source/list.c


queue.o: ../../../../Source/queue.c $(FreeRTOS) $(task) $(croutine)
	mb-gcc -c ../../../../Source/queue.c

tasks.o: ../../../../Source/tasks.c $(FreeRTOS) $(task) $(StackMacros) $(xintc_l) 
	mb-gcc -c ../../../../Source/tasks.c
	

port.o: port.c $(FreeRTOS) $(task) $(xparameters) $(xintc) $(xintc_i) $(xtmrctr)
	mb-gcc -c port.c


portasm.o: portasm.s 
	mb-gcc -c portasm.s


heap_1.o: ../../../../Source/portable/MemMang/heap_1.c $(FreeRTOS) $(task)
	mb-gcc -c ../../../../Source/portable/MemMang/heap_1.c


microblaze_disable_interrupts.o: microblaze_disable_interrupts.s
	mb-gcc -c microblaze_disable_interrupts.s


microblaze_enable_interrupts.o: microblaze_enable_interrupts.s
	mb-gcc -c microblaze_enable_interrupts.s
