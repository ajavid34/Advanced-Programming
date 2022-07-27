COMPILER=g++
VERSION= -std=c++11
CC=${COMPILER} ${VERSION}
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: doodleJump.out

doodleJump.out: main.o rsdl.o Game.o Defines.o Objects.o
	$(CC) main.o rsdl.o Game.o Defines.o Objects.o $(CCFLAGS) -o doodleJump.out

main.o: src/rsdl.hpp  main.cpp Game.o
	$(CC) -c main.cpp -o main.o

rsdl.o: src/rsdl.hpp src/rsdl.cpp
	$(CC) -c src/rsdl.cpp -o rsdl.o

Defines.o: Defines.cpp Defines.hpp
	$(CC) -c Defines.cpp

Objects.o: src/rsdl.hpp  Objects.hpp Objects.cpp Defines.hpp
	$(CC) -c Objects.cpp

Game.o: src/rsdl.hpp  Game.cpp Game.hpp Defines.hpp Objects.hpp Objects.cpp
	$(CC) -c Game.cpp
	
.PHONY: clean
clean:
	rm -r *.o
	rm doodleJump.out