CC = g++
CFLAGS = -c -std=c++11

all: problem
	./problem
problem: main.o board.o pawn.o square.o
	$(CC) -o problem main.o board.o pawn.o square.o
main.o: main.cpp board.hh square.hh pawn.hh problem.hh solutions.hh
	$(CC) $(CFLAGS) main.cpp
board.o: board.cpp board.hh square.hh pawn.hh
	$(CC) $(CFLAGS) board.cpp
square.o: square.cpp board.hh square.hh pawn.hh
	$(CC) $(CFLAGS) square.cpp
pawn.o: pawn.cpp board.hh square.hh pawn.hh
	$(CC) $(CFLAGS) pawn.cpp
clean:
	rm *.o checkers