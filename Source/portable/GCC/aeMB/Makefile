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
Cheap_1 = ../../../../Source/portable/MemMang/heap_1.c
Cheap_2 = ../../../../Source/portable/MemMang/heap_2.c
Cheap_3 = ../../../../Source/portable/MemMang/heap_3.c
#.......................................................
#-Wl,-defsym -Wl,_STACK_SIZE=0x400 -Wl,-defsym -Wl,_HEAP_SIZE=0x8000


compile: main.o list.o queue.o tasks.o port.o portasm.o heap_3.o
	mb-gcc -Wl,-defsym -Wl,_HEAP_SIZE=0x8000 -mtune=v5.00 -mxl-soft-div -msoft-float -mxl-barrel-shift -mno-xl-soft-mul *.o -O1

main.o: main.c $(HFreeRTOS) $(Htask)
	mb-gcc -mtune=v5.00 -mxl-soft-div -msoft-float -mxl-barrel-shift -mno-xl-soft-mul -c main.c -O1


list.o: $(Clist) $(HFreeRTOS) $(Hlist)
	mb-gcc  -mtune=v5.00 -mxl-soft-div -msoft-float -mxl-barrel-shift -mno-xl-soft-mul -c $(Clist) -O1


queue.o: $(Cqueue) $(HFreeRTOS) $(Htask) $(Hcroutine)
	mb-gcc  -mtune=v5.00 -mxl-soft-div -msoft-float -mxl-barrel-shift -mno-xl-soft-mul -c $(Cqueue) -O1

tasks.o: $(Ctasks)  $(HFreeRTOS) $(Htask) $(HStackMacros)  
	mb-gcc  -mtune=v5.00 -mxl-soft-div -msoft-float -mxl-barrel-shift -mno-xl-soft-mul -c $(Ctasks) -O1
	

port.o: port.c $(HFreeRTOS) $(Htask) 
	mb-gcc  -mtune=v5.00 -mxl-soft-div -msoft-float -mxl-barrel-shift -mno-xl-soft-mul -c port.c -O1


portasm.o: portasm.s 
	mb-gcc  -mtune=v5.00 -mxl-soft-div -msoft-float -mxl-barrel-shift -mno-xl-soft-mul -c portasm.s -O1


#heap_1.o: $(Cheap_1) $(HFreeRTOS) $(Htask)
#	mb-gcc -mtune=v5.00 -mxl-soft-div -msoft-float -mxl-barrel-shift -mno-xl-soft-mul -c $(Cheap_1) -O1


#heap_2.o: $(Cheap_2) $(HFreeRTOS) $(Htask)
#	mb-gcc -mtune=v5.00 -mxl-soft-div -msoft-float -mxl-barrel-shift -mno-xl-soft-mul) -c $(Cheap_2) -O1

heap_3.o: $(Cheap_3) $(HFreeRTOS) $(Htask)
	mb-gcc -mtune=v5.00 -mxl-soft-div -msoft-float -mxl-barrel-shift -mno-xl-soft-mul -c $(Cheap_3) -O1


