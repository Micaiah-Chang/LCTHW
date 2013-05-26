CFLAGS=-Wall -g

all:
	cc ex1.c -o ex1
	cc ex2.c -o ex2
	cc ex4.c -o ex4

clean:
	rm -f ex1 ex2 ex4 ex5

ex1:
	cc ex1.c -o ex1

ex2:
	cc ex2.c -o ex2

ex4:
	cc ex4.c -o ex4

ex5:
	cc ex5.c -o ex5

ex6:
	cc ex6.c -o ex6
