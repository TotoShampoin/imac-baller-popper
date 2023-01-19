EXEC=bin/ballers

CC=g++

RESOURCES=main displayator vector ball linkedlistball wall SDL2_gfxPrimitives

CFLAGS=-std=c++17 -Wall -Wextra -g
LFLAGS=-Iinclude
LFLAGS-SDL=`pkg-config --cflags --libs  sdl2 SDL2_image SDL2_ttf SDL2_mixer`

all: $(EXEC)

obj/%.o: src/%.cpp
	mkdir -p obj
	$(CC) $(CFLAGS) -c $^ -o $@ $(LFLAGS)

# 			obj/$(RESOURCES).o
$(EXEC): $(addprefix obj/, $(addsuffix .o, $(RESOURCES)))
	mkdir -p bin
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS) $(LFLAGS-SDL)
	cp -r assets bin/assets

clean:
	rm obj/*
	rm $(EXEC)
