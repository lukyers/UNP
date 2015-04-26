all: liberr.a

liberr.a: liberr.o
	ar rv liberr.a liberr.o
liberr.o: error.c error.h common.h
	gcc error.c -c -o liberr.o

clean:
	rm -rf *.o *.a
