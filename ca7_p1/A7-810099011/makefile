COMPILER=g++
VERSION= -std=c++11
CC=${COMPILER} ${VERSION}

all: goodeats.out

goodeats.out: main.o Errors.o App.o Recipes.o Shelves.o Sort_And_Find.o Users.o Filters.o Voter.o
	$(CC) main.o Errors.o App.o Recipes.o Shelves.o Sort_And_Find.o Users.o Filters.o Voter.o -o goodeats.out

main.o: main.cpp App.o Errors.o
	$(CC) -c main.cpp -o main.o

Errors.o: Errors.hpp Errors.cpp Includes_And_Defines.hpp
	$(CC) -c Errors.cpp -o Errors.o

Recipes.o:  Recipes.hpp Recipes.cpp Includes_And_Defines.hpp Users.hpp Voter.hpp Sort_And_Find.hpp
	$(CC) -c Recipes.cpp -o Recipes.o

App.o:  App.cpp App.hpp Includes_And_Defines.hpp Recipes.hpp Users.hpp Shelves.hpp Filters.hpp Sort_And_Find.hpp
	$(CC) -c App.cpp -o App.o

Shelves.o: Shelves.cpp Shelves.hpp Includes_And_Defines.hpp Recipes.hpp Users.hpp Sort_And_Find.hpp Errors.hpp
	$(CC) -c Shelves.cpp -o Shelves.o

Sort_And_Find.o: Sort_And_Find.cpp Sort_And_Find.hpp Shelves.hpp Includes_And_Defines.hpp Recipes.hpp Users.hpp 
	$(CC) -c Sort_And_Find.cpp -o Sort_And_Find.o

Users.o: Users.cpp Users.hpp Includes_And_Defines.hpp Recipes.hpp Shelves.hpp Sort_And_Find.hpp Errors.hpp
	$(CC) -c Users.cpp -o Users.o
	
Filters.o: Filters.cpp Filters.hpp Includes_And_Defines.hpp Recipes.hpp Errors.hpp
	$(CC) -c Filters.cpp -o Filters.o

Voter.o: Voter.cpp Voter.hpp Includes_And_Defines.hpp Users.hpp
	$(CC) -c Voter.cpp -o Voter.o

.PHONY: clean
clean:
	rm -r *.o
	rm goodeats.out