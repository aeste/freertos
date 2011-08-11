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

FreeRTOS = ../FreeRTOS/Source/include/FreeRTOS.h
FRTOSINC = -I../FreeRTOS/Source/include/ -I../aemb/ -I./

CC = mb-gcc
COPTS = -mxl-barrel-shift -mno-xl-soft-mul -Wall
OOPTS = -Os -g2 -finline-functions
LOPTS = -Wl,-defsym -Wl,_HEAP_SIZE=0x8000

all: freertos srec dump

freertos: main.o list.o queue.o tasks.o port.o heap_3.o portasm.o
	$(CC) $(COPTS) $(LOPTS) $(OOPTS) *.o -o freertos.o

main.o: main.c $(FreeRTOS)
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c main.c

list.o: ../FreeRTOS/Source/list.c ../FreeRTOS/Source/include/list.h $(FreeRTOS)
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/list.c

queue.o: ../FreeRTOS/Source/queue.c ../FreeRTOS/Source/include/queue.h $(FreeRTOS)
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/queue.c

tasks.o: ../FreeRTOS/Source/tasks.c  ../FreeRTOS/Source/include/task.h $(FreeRTOS)
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/tasks.c
	
port.o: ../aemb/port.c ../aemb/port.h $(FreeRTOS) 
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../aemb/port.c

portasm.o: ../aemb/portasm.s $(FreeRTOS)
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../aemb/portasm.s

heap_3.o: ../FreeRTOS/Source/portable/MemMang/heap_3.c $(FreeRTOS)
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/portable/MemMang/heap_3.c

srec: freertos
	mb-objcopy -O srec freertos.o freertos.srec
	
dump: freertos
	mb-objdump -DSC freertos.o > freertos.S

clean:
	rm -f freertos.*
	rm -f *.o
