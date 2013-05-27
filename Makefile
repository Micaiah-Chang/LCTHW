CFLAGS=-Wall -g

clean:
	rm -f ex1 ex2 ex4 ex5 ex6 ex7

ex7:
	cc ex7.c -o ex7

ex6:
	cc ex6.c -o ex6

ex5:
	cc ex5.c -o ex5

ex4:
	cc ex4.c -o ex4

ex2:
	cc ex2.c -o ex2

ex1:
	cc ex1.c -o ex1

all:
	cc ex1.c -o ex1
	cc ex2.c -o ex2
	cc ex4.c -o ex4
	cc ex6.c -o ex6
	cc ex7.c -o ex7
