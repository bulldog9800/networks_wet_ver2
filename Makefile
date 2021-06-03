HEADERS = simulator.h timer.h
COMPILER = g++
FLAGS = -std=c++11

default: simulator

simulator.o: simulator.cpp $(HEADERS)
	${COMPILER} ${FLAGS} -c simulator.cpp -o simulator.o

main.o: main.cpp $(HEADERS)
	${COMPILER} ${FLAGS} -c main.cpp -o main.o

timer.o: timer.cpp $(HEADERS)
	${COMPILER} ${FLAGS} -c timer.cpp -o timer.o

simulator: simulator.o main.o timer.o
	${COMPILER} main.o simulator.o timer.o -o simulator

clean:
	-rm -f simulator.o
	-rm -f main.o
	-rm -f timer.o
	-rm -f simulator
