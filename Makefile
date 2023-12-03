CFLAGS =-Wall -g

all : ex19

ex19: object.o

.PHONY : all clean

clean :
	rm -f object.o
	rm -f ex19
