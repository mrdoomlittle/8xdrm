CFLAGS=-I/usr/local/include
ARC=-DARC64
F_CPU=16000000UL
DEVICE=atmega328p
all:
	avr-gcc -c -g $(ARC) $(CFLAGS) -D__AVR -std=c11 -DF_CPU=$(F_CPU) -Os -mmcu=$(DEVICE) -o bitct.o bitct.c
	ar rc lib/libmdl-bitct.a bitct.o
	cp bitct.h inc/mdl
clean:
	sh clean.sh
