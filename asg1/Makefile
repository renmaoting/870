CFLAGS  = -g -Wall -Weffc++ -Wextra -pedantic
LDFLAGS =

run:main.o game.o source.o 
	g++ ${CFLAGS} -o run main.o game.o source.o ${LDFLAGS}

main.o:	main.cpp game.h source.h
	g++ ${CFLAGS} -c main.cpp

source.o: source.h source.cpp
	g++ ${CFLAGS} -c source.cpp
game.o: game.h source.h source.cpp game.cpp
	g++ ${CFLAGS} -c game.cpp

clean:
	rm -rf *.o
	rm -rf *~
	rm -rf run a.out
