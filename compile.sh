gcc -c -std=c11 -o 8xdrm.o 8xdrm.c
ar rc lib/lib8xdrm.a 8xdrm.o
cp 8xdrm.h inc


gcc -std=c11 -o main main.c 8xdrm.o
