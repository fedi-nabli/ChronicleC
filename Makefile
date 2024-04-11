OBJECTS = ./build/chronoc.o
INCLUDES = -I./includes

LIB_NAME = ./lib/chronoc.a
SHARED_LIB_NAME = ./lib/chronoc.so

all: ${OBJECTS} ${SHARED_LIB_NAME}
	ar rcs ./lib/chronoc.a ${OBJECTS}

./build/chronoc.o: ./src/chroniclec.c
	gcc ${INCLUDES} ./src/chroniclec.c -g -c -fPIC -o ./build/chronoc.o

$(SHARED_LIB_NAME): ./src/chroniclec.c
	gcc -shared -o ${SHARED_LIB_NAME} ${OBJECTS}

clean:
	rm -rf ${OBJECTS}
	rm -rf ${LIB_NAME}
	rm -rf ${SHARED_LIB_NAME}