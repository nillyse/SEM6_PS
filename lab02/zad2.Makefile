outprogname : zad2.o func.o
	gcc -o outprogname zad2.o func.o

func.o : func.c
	gcc -c func.c

zad2.o : zad2.c
	gcc -c zad2.c