CFLAGS=-g -O2 -Wall -Wextra -Isrc $(shell pkg-config --cflags libbsd) -rdynamic -DNDEBUG $(OPTFLAGS)
COMMON_LIBS=$(shell pkg-config --libs libbsd) -ldl -lrt -lm $(OPTLIBS) -llcthw
LDLIBS=$(COMMON_LIBS)
PREFIX?=/usr/local

TARGET=liblcthw.a

SOURCES=$(wildcard liblcthw/src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

clean:
	rm -f ./bin/*
	rm -f ex22.o
	rm -f ex22_main

ex24:
	cc ex24.c -o ./bin/ex24

ex23:
	cc ex23.c -lrt -o ./bin/ex23

ex22_main: ex22.o


ex20:
	cc -Wall -g -DNDEBUG ex20.c -o ./bin/ex20

stack:
	cc stack.c -o ./bin/stack

ex18:
	cc ex18.c -o ./bin/ex18

ex17:
	cc ex17.c -o ./bin/ex17

ex16:
	cc ex16.c -o ./bin/ex16

ex15:
	cc ex15.c -o ./bin/ex15

ex14:
	cc ex14.c -o ./bin/ex14

ex13:
	cc ex13.c -o ./bin/ex13

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
	cc ex12.c -o ./bin/ex13
	cc ex14.c -o ./bin/ex14
	cc ex15.c -o ./bin/ex15
	cc ex16.c -o ./bin/ex16
	cc ex17.c -o ./bin/ex17
	cc ex18.c -o ./bin/ex18
	cc ex20.c -o ./bin/ex20
