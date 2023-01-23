EXEC=bin/ballers

CC=g++

RESOURCES=SDL2_gfxPrimitives string_manip displayator vector ball linkedlistball wall level menu main

CFLAGS=-std=c++17 -Wall -Wextra -g
LFLAGS=-Iinclude
LFLAGS-SDL=`pkg-config --cflags --libs  sdl2 SDL2_image SDL2_ttf SDL2_mixer`

all:
	mkdir -p bin
	mkdir -p obj
	make $(EXEC)

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@ $(LFLAGS)

obj/SDL2_gfxPrimitives.o: src/SDL2_gfxPrimitives.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(LFLAGS)

# 			obj/$(RESOURCES).o
$(EXEC): $(addprefix obj/, $(addsuffix .o, $(RESOURCES)))
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS) $(LFLAGS-SDL)
	cp -r assets bin/

clean:
	rm obj/*
	rm $(EXEC)
