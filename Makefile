CC = gcc
AR = ar
WARNINGS = -Wall

SRC = $(wildcard src/*.c)
TESTS = $(wildcard tests/*.c)

OBJS := $(SRC:src/%.c=bin/%.o)


bin/%.o: src/%.c
	$(CC) -c $< --std=c99 $(WARNINGS) -o $@ -fPIC

build: $(OBJS)
	$(AR) rcs bin/libcnsrenderer.a $(OBJS)

test-%: tests/%.c build
	$(CC) $< --std=c99 $(WARNINGS) -o bin/$@ -I./src -L./bin -lcnsrenderer