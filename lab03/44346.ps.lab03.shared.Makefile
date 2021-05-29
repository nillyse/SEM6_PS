#PS IS1 321 LAB02 
#Roksana Jarema 
#jr44346@zut.edu.pl 

pre=44346.ps.lab03.shared.

sshared : zad2.o libtest.so.0.1
	gcc zad2.o -o sshared -ldl

libtest.so.0.1 : dshared.o
	gcc -shared -nostartfiles dshared.o -o libtest.so.0.1 -fPIC

dshared.o : $(pre)lib.c
	gcc -c 44346.ps.lab03.shared.lib.c -o dshared.o -fPIC

zad2.o : $(pre)main.c
	gcc -c $(pre)main.c -o zad2.o