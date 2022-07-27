COMPILER=g++
VERSION= -std=c++11
CC=${COMPILER} ${VERSION}

all: goodeats.out

template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) -c utils/template_parser.cpp -o template_parser.o

response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) -c utils/response.cpp -o response.o

request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) -c utils/request.cpp -o request.o

utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) -c utils/utilities.cpp -o utilities.o

server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) -c server/server.cpp -o server.o

route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) -c server/route.cpp -o route.o

handlers.o: handlers.cpp handlers.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp App.hpp
	$(CC) -c handlers.cpp -o handlers.o

my_server.o: my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) -c my_server.cpp -o my_server.o

main.o: main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp App.hpp Errors.hpp handlers.hpp
	$(CC) -c main.cpp -o main.o

goodeats.out: main.o Errors.o App.o Recipes.o Shelves.o Sort_And_Find.o Users.o Filters.o Voter.o Order.o Ingredient.o my_server.o handlers.o route.o server.o utilities.o request.o response.o template_parser.o
	$(CC) main.o Errors.o App.o Recipes.o Shelves.o Sort_And_Find.o Users.o Filters.o Voter.o Order.o Ingredient.o my_server.o handlers.o route.o server.o utilities.o request.o response.o template_parser.o -o goodeats.out

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

Order.o: Order.cpp Order.hpp Includes_And_Defines.hpp Errors.hpp Ingredient.hpp
	$(CC) -c Order.cpp -o Order.o

Ingredient.o: Ingredient.cpp Ingredient.hpp Users.hpp
	$(CC) -c Ingredient.cpp -o Ingredient.o

.PHONY: clean
clean:
	rm -r *.o
	rm goodeats.out
