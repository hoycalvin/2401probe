OBJ = a5main.o

a5main.o:	a5main.c
		gcc -c a5main.c

a5:		a5main.o
		gcc -o a5 a5main.o

