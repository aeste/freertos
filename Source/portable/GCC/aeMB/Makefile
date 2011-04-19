#................. headers include......................

HFreeRTOS = ../../../../Source/include/FreeRTOS.h
Htask = ../../../../Source/include/task.h
Hlist = ../../../../Source/include/list.h
Hcroutine = ../../../../Source/include/croutine.h
HStackMacros = ../../../../Source/include/StackMacros.h
#.......................................................
#...................Sourec files........................
Clist = ../../../../Source/list.c
Cqueue = ../../../../Source/queue.c
Ctasks = ../../../../Source/tasks.c 
Cheap_3 = ../../../../Source/portable/MemMang/heap_3.c
#.......................................................

XILFLAGS="-mtune=v5.00 -mxl-soft-div -msoft-float -mxl-barrel-shift -mno-xl-soft-mul"


compile: main.o list.o queue.o tasks.o port.o portasm.o heap_3.o
	mb-gcc *.o -O2

main.o: main.c $(HFreeRTOS) $(Htask)
	mb-gcc $(XILFLAGS) -c main.c -O2


list.o: $(Clist) $(HFreeRTOS) $(Hlist)
	mb-gcc $(XILFLAGS) -c $(Clist) -O2


queue.o: $(Cqueue) $(HFreeRTOS) $(Htask) $(Hcroutine)
	mb-gcc $(XILFLAGS) -c $(Cqueue) -O2

tasks.o: $(Ctasks)  $(HFreeRTOS) $(Htask) $(HStackMacros)  
	mb-gcc $(XILFLAGS) -c $(Ctasks) -O2
	

port.o: port.c $(HFreeRTOS) $(Htask) 
	mb-gcc $(XILFLAGS) -c port.c -O2


portasm.o: portasm.s 
	mb-gcc $(XILFLAGS) -c portasm.s -O2


heap_3.o: $(Cheap_3) $(HFreeRTOS) $(Htask)
	mb-gcc $(XILFLAGS) -c $(Cheap_3) -O2


