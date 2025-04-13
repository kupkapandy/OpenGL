CC = gcc
CCFLAGS = -Wall -Wextra -Wpedantic -g -Wfloat-equal -fno-strict-aliasing
CCFLAGS += -Wno-pointer-arith -Wno-unused-parameter
CCFLAGS += -O2 -g
CCFLAGS += -Ilib/cglm/include -Ilib/glad/include -Ilib/glfw/include
LDFLAGS = lib/glad/src/glad.o lib/cglm/libcglm.a lib/glfw/src/libglfw3.a -lm -ldl -lpthread

SRC = $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/**/**/*.c)
OBJ = $(SRC:.c=.o)
BIN = bin

.PHONY: all clean

all: dirs libs main

libs:
	cd lib/glfw && cmake . && make
	cd lib/cglm && cmake . -DCGLM_STATIC=ON && make
	cd lib/glad && $(CC) -o src/glad.o -I include -c src/glad.c

dirs:
	mkdir -p ./$(BIN)

run: all
	$(BIN)/main

main: $(OBJ)
	$(CC) -o $(BIN)/main $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CCFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)
