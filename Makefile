CC = gcc
AR = ar
WARNINGS = -Wall

SRC = $(wildcard src/*.c)
TESTS = $(wildcard tests/*.c)

OBJS := $(SRC:src/%.c=src/%.o)
CPPFLAGS := --std=c99 $(WARNINGS) -fPIC -I./headers


build: $(OBJS)
	$(AR) rcs bin/libcnsrenderer.a $(OBJS)

test-%: tests/%.c build
	$(CC) $< --std=c99 $(WARNINGS) -o bin/$@ -I./headers -L./bin -lcnsrenderer -lm

clean:
	rm $(OBJS)