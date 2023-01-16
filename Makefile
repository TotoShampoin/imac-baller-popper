EXEC=bin/ballers

CC=g++

RESOURCES=main displayator vector ball linkedlistball wall

CFLAGS=-std=c++17 -Wall -Wextra -g
LFLAGS=-Iinclude
LFLAGS-SDL=`pkg-config --cflags --libs  sdl2 SDL2_gfx SDL2_image SDL2_ttf SDL2_mixer`

all: $(EXEC)

obj/%.o: src/%.cpp
	mkdir -p obj
	$(CC) $(CFLAGS) $(LFLAGS) -c $^ -o $@

obj/displayator.o: src/displayator.cpp
	$(CC) $(CFLAGS) $(LFLAGS) $(LFLAGS-SDL) -c $^ -o $@

# 			obj/$(RESOURCES).o
$(EXEC): $(addprefix obj/, $(addsuffix .o, $(RESOURCES)))
	mkdir -p bin
	$(CC) $(CFLAGS) $(LFLAGS) $(LFLAGS-SDL) $^ -o $@
	cp -r assets bin/assets

clean:
	rm obj/*
	rm $(EXEC)
