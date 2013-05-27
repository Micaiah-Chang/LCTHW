CFLAGS=-Wall -g

clean:
	rm -f ./bin/*

ex7:
	cc ex7.c -o ./bin/ex7

ex6:
	cc ex6.c -o ./bin/ex6

ex5:
	cc ex5.c -o ./bin/ex5

ex4:
	cc ex4.c -o ./bin/ex4

ex2:
	cc ex2.c -o ./bin/ex2

ex1:
	cc ex1.c -o ./bin/ex1

all:
	cc ex1.c -o ./bin/ex1
	cc ex2.c -o ./bin/ex2
	cc ex4.c -o ./bin/ex4
	cc ex6.c -o ./bin/ex6
	cc ex7.c -o ./bin/ex7
