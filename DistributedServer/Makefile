PROJECT_NAME=distributed_server

C_SRC=$(wildcard src/*.c)

H_SRC=$(wildcard inc/*.h)

OBJ=$(subst .c,.o,$(subst src,obj,$(C_SRC)))

CC=gcc

CC_FLAGS = -Wall -c -O2 -static -I inc

all: objFolder $(PROJECT_NAME)

clean:
	rm -rf obj/*.o *.bin

$(PROJECT_NAME): $(OBJ)
	$(CC) -o $@.bin $^ -lwiringPi -pthread

obj/%.o: src/%.c inc/%.h
	$(CC) -o $@ $< $(CC_FLAGS)

obj/main.o: src/main.c $(H_SRC)
	$(CC) -o $@ $< $(CC_FLAGS)

objFolder:
	mkdir -p obj