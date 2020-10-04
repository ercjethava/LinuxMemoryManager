CC=gcc 
CFLAGS=-g -Wall
LDFLAGS= -shared
CURRENT_DIR = $(shell pwd)
GLUETHREAD_DIR = ${CURRENT_DIR}/../gluelist
OBJS=${GLUETHREAD_DIR}/gluelist.o memory_manager.o
TAREGT_LIB=libmemory.so


TAREGT_LIB:${OBJS}
	${CC} ${LDFLAGS} ${OBJS} -o ${TAREGT_LIB}
	cp ${TAREGT_LIB} ${CURRENT_DIR}/../
${GLUETHREAD_DIR}/gluelist.o:${GLUETHREAD_DIR}/gluelist.c
	${CC} ${CFLAGS} -c -fpic ${GLUETHREAD_DIR}/gluelist.c -o ${GLUETHREAD_DIR}/gluelist.o
memory_manager.o:memory_manager.c
	${CC} ${CFLAGS} -c -fpic -I ${CURRENT_DIR}/.. memory_manager.c -o memory_manager.o

clean:
	rm -f ${TAREGT_LIB}
	rm -f ${OBJS}
	rm -f ${GLUETHREAD_DIR}/*.gch *.gch
