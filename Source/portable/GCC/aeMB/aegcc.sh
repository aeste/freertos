#!/bin/sh

# Remove all the object files and srecord files
rm -f *.o a.out a.srec ../../../../../aemb/sim/dump.vmem

# Compile and link the project files
make

# Convert the ELF file to an SREC file
mb-objcopy -O srec a.out a.srec 

# Generate a Verilog VMEM file from the SREC file
srec_cat a.srec -o ../../../../../aeste/sim/dump.vmem -vmem 32

# Remove all the object files and srecord files
rm -f *.o a.srec
