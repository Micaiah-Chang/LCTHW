CFLAGS=-Wall -g

clean:
	rm -f ./bin/*

ex12:
	cc ex12.c -o ./bin/ex12

ex11:
	cc ex11.c -o ./bin/ex11

ex10:
	cc ex10.c -o ./bin/ex10

ex9:
	cc ex9.c -o ./bin/ex9

ex8:
	cc ex8.c -o ./bin/ex8

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
	cc ex8.c -o ./bin/ex8
	cc ex9.c -o ./bin/ex9
	cc ex10.c -o ./bin/ex10
	cc ex11.c -o ./bin/ex11
	cc ex12.c -o ./bin/ex12
