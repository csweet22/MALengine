CC=g++
CFLAGS= -w -lglfw -lGL -lGLEW -lGLU
fullFlags= -Wall -Wpedantic -Wextra -std=gnu17 -lglfw -lGL -lGLEW

default:
	make all

all:
	$(CC) -o bin/Ash src/*.cpp $(CFLAGS)

clean:
	rm -f Ash

run: all
	./bin/Ash
