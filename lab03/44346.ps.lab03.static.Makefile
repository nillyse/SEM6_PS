#PS IS1 321 LAB02 
#Roksana Jarema 
#jr44346@zut.edu.pl 

pre=44346.ps.lab03.static.

outprogname : zad1.o libbib.a
	gcc zad1.o -o outprogname -L. -lbib

libbib.a : lib.o
	ar cr libbib.a lib.o

lib.o : $(pre)lib.c
	gcc -c $(pre)lib.c -o lib.o

zad1.o : $(pre)main.c
	gcc -c $(pre)main.c -o zad1.o