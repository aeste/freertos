FREERTOS = ../FreeRTOS/Source/include/FreeRTOS.h
FRTOSINC = -I../FreeRTOS/Source/include/ -I../FreeRTOS/Source/portable/AEMB2/ -I./

AR = mb-ar
CC = mb-gcc
CXX = mb-g++
COPTS = -Wall -mxl-barrel-shift -mno-xl-soft-mul
# -xl-mode-bootstrap
OOPTS = -Os
# -finline-functions
LOPTS = -Wl,-defsym -Wl,_HEAP_SIZE=0x8000 -Wl,--entry=_vector_reset -Wl,--script=aemb.ld
# -nostartfiles -Ttext 0x400 -e __start -Wl,-defsym -Wl,_TEXT_START_ADDR=0x30 

all: freertos srec dump vmem
#	rm -f *.o
	
#freertos: main.o list.o queue.o tasks.o port.o heap.o portasm.o #crt.o
#	$(CXX) $(COPTS) $(LOPTS) $(OOPTS) *.o -o freertos.o

freertos: main.o freertos.a
	$(CXX) $(COPTS) $(LOPTS) $(OOPTS) main.o freertos.a -o freertos.o

freertos.a: list.o queue.o tasks.o port.o heap.o portasm.o #crt.o
	$(AR) cr freertos.a *.o

main.o: main.cc $(FREERTOS)
	$(CXX) $(COPTS) $(OOPTS) $(FRTOSINC) -c main.cc

list.o: ../FreeRTOS/Source/list.c ../FreeRTOS/Source/include/list.h $(FREERTOS)
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/list.c

queue.o: ../FreeRTOS/Source/queue.c ../FreeRTOS/Source/include/queue.h $(FREERTOS)
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/queue.c

tasks.o: ../FreeRTOS/Source/tasks.c  ../FreeRTOS/Source/include/task.h $(FREERTOS)
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/tasks.c
	
port.o: ../FreeRTOS/Source/portable/AEMB2/port.c ../FreeRTOS/Source/portable/AEMB2/port.h $(FREERTOS) 
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/portable/AEMB2/port.c

portasm.o: ../FreeRTOS/Source/portable/AEMB2/portasm.S $(FREERTOS)
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/portable/AEMB2/portasm.S

crt.o: ../FreeRTOS/Source/portable/AEMB2/crt.S $(FREERTOS)
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/portable/AEMB2/crt.S
#	mb-as ../aemb/crt.S -o crt.o

heap.o: ../FreeRTOS/Source/portable/MemMang/heap_1.c $(FREERTOS)
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/portable/MemMang/heap_1.c -o heap.o

#heap.o: ../FreeRTOS/Source/portable/MemMang/heap_2.c $(FREERTOS)
#	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/portable/MemMang/heap_2.c -o heap.o

#heap.o: ../FreeRTOS/Source/portable/MemMang/heap_3.c $(FREERTOS)
#	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/portable/MemMang/heap_3.c -o heap.o

srec: freertos
	mb-objcopy -O srec freertos.o freertos.srec
	
dump: freertos
	mb-objdump -dSC freertos.o > freertos.S

vmem: srec
	srec_cat freertos.srec -fill 0xAE -within freertos.srec -range-pad 4 -o freertos.vmem -vmem 32
	
clean:
	rm -f freertos.*
	rm -f *.o *.a
