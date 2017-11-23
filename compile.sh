gcc -c -std=c11 $1 -o bitct.o bitct.c
ar rc lib/libmdl-bitct.a bitct.o
cp bitct.h inc/mdl


gcc -std=c11 $1 -o main main.c bitct.o
