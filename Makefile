CFLAGS=-I/usr/local/include
ARC=-DARC64
F_CPU=16000000UL
DEVICE=atmega328p
all:
	avr-gcc -c -g $(ARC) $(CFLAGS) -D__AVR -std=c11 -DF_CPU=$(F_CPU) -Os -mmcu=$(DEVICE) -o 8xdrm.o 8xdrm.c
	ar rc lib/lib8xdrm.a 8xdrm.o
	cp 8xdrm.h inc
clean:
	sh clean.sh
