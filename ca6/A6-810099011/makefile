COMPILER=g++
VERSION= -std=c++11
CC=${COMPILER} ${VERSION}

all: ‫‪permitMaker‬‬.out

‫‪permitMaker‬‬.out: main.o Permits.o App.o Defines.o Form.o
	$(CC) main.o Permits.o App.o Defines.o Form.o -o ‫‪permitMaker‬‬.out

main.o: main.cpp App.o
	$(CC) -c main.cpp -o main.o

Permits.o: Permits.hpp Permits.cpp Form.hpp Defines.hpp
	$(CC) -c Permits.cpp -o Permits.o

Defines.o: Defines.cpp Defines.hpp
	$(CC) -c Defines.cpp

Form.o:  Form.hpp Form.cpp Defines.hpp
	$(CC) -c Form.cpp

App.o:  App.cpp App.hpp Defines.hpp Form.hpp Permits.hpp
	$(CC) -c App.cpp
	
.PHONY: clean
clean:
	rm -r *.o
	rm ‫‪permitMaker‬‬.out