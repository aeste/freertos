FreeRTOS = ../FreeRTOS/Source/include/FreeRTOS.h
FRTOSINC = -I../FreeRTOS/Source/include/ -I../FreeRTOS/Source/portable/AEMB2/ -I./

CC = mb-gcc
COPTS = -Wall -mxl-barrel-shift -mno-xl-soft-mul
# -xl-mode-bootstrap
OOPTS = -Os
# -finline-functions
LOPTS = -Wl,-defsym -Wl,_HEAP_SIZE=0x8000 -Wl,--entry=_vector_reset -Wl,--script=aemb.ld
# -nostartfiles -Ttext 0x400 -e __start -Wl,-defsym -Wl,_TEXT_START_ADDR=0x30 

all: freertos srec dump vmem
#	rm -f *.o
	
freertos: main.o list.o queue.o tasks.o port.o heap.o portasm.o #crt.o
	$(CC) $(COPTS) $(LOPTS) $(OOPTS) *.o -o freertos.o

main.o: main.c $(FreeRTOS)
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c main.c

list.o: ../FreeRTOS/Source/list.c ../FreeRTOS/Source/include/list.h $(FreeRTOS)
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/list.c

queue.o: ../FreeRTOS/Source/queue.c ../FreeRTOS/Source/include/queue.h $(FreeRTOS)
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/queue.c

tasks.o: ../FreeRTOS/Source/tasks.c  ../FreeRTOS/Source/include/task.h $(FreeRTOS)
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/tasks.c
	
port.o: ../FreeRTOS/Source/portable/AEMB2/port.c ../FreeRTOS/Source/portable/AEMB2/port.h $(FreeRTOS) 
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/portable/AEMB2/port.c

portasm.o: ../FreeRTOS/Source/portable/AEMB2/portasm.S $(FreeRTOS)
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/portable/AEMB2/portasm.S

crt.o: ../FreeRTOS/Source/portable/AEMB2/crt.S $(FreeRTOS)
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/portable/AEMB2/crt.S
#	mb-as ../aemb/crt.S -o crt.o

heap.o: ../FreeRTOS/Source/portable/MemMang/heap_1.c $(FreeRTOS)
	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/portable/MemMang/heap_1.c -o heap.o

#heap.o: ../FreeRTOS/Source/portable/MemMang/heap_2.c $(FreeRTOS)
#	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/portable/MemMang/heap_2.c -o heap.o

#heap.o: ../FreeRTOS/Source/portable/MemMang/heap_3.c $(FreeRTOS)
#	$(CC) $(COPTS) $(OOPTS) $(FRTOSINC) -c ../FreeRTOS/Source/portable/MemMang/heap_3.c -o heap.o

srec: freertos
	mb-objcopy -O srec freertos.o freertos.srec
	
dump: freertos
	mb-objdump -dSC freertos.o > freertos.S

vmem: srec
	srec_cat freertos.srec -fill 0xAE -within freertos.srec -range-pad 4 -o freertos.vmem -vmem 32
	
clean:
	rm -f freertos.*
	rm -f *.o
