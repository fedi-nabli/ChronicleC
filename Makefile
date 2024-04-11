OBJECTS = ./build/chronoc.o
INCLUDES = -I./includes

LIB_NAME = ./lib/chronoc.a

all: ${OBJECTS}
	ar rcs ./lib/chronoc.a ${OBJECTS}

./build/chronoc.o: ./src/chroniclec.c
	gcc ${INCLUDES} ./src/chroniclec.c -g -c -o ./build/chronoc.o

clean:
	rm -rf ${OBJECTS}
	rm -rf ${LIB_NAME}