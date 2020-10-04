CC=gcc 
CFLAGS=-g -Wall
EXTERNAL_LIBS= -lmemory
TAREGT_APP= test_app
LDPATH = $(shell pwd)

TAREGT_APP:testapp.o
	${CC} ${CFLAGS} -L${LDPATH} testapp.o -o ${TAREGT_APP} ${EXTERNAL_LIBS}
testapp.o:testapp.c
	${CC} ${CFLAGS} -c testapp.c -o testapp.o

clean:
	rm -f testapp.o
	rm -f *.gch
