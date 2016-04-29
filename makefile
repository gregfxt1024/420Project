# Makefile for the executable genetic algorithm


project: main.o toffoli_gate.o genetic.o astar.o Node.o
	g++ -std=c++14 -o project main.o toffoli_gate.o genetic.o astar.o Node.o

main.o: main.cpp genetic.h
	g++ -c -g -std=c++14 -Wall -Wextra -pedantic main.cpp genetic.h

astar.o: astar.cpp toffoli_gate.h genetic.h astar.h Node.h
	g++ -c -g -std=c++14 -Wall -Wextra -pedantic astar.cpp toffoli_gate.h genetic.h astar.h Node.h

Node.o: Node.cpp Node.h genetic.h toffoli_gate.h
	g++ -c -g -std=c++14 -Wall -Wextra -pedantic Node.cpp Node.h genetic.h toffoli_gate.h

genetic.o: genetic.cpp toffoli_gate.h genetic.h
	g++ -c -g -std=c++14 -Wall -Wextra -pedantic genetic.cpp genetic.h toffoli_gate.h

toffoli_gate.o: toffoli_gate.cpp toffoli_gate.h
	g++ -c -g -std=c++14 -Wall -Wextra -pedantic toffoli_gate.cpp toffoli_gate.h

clean:
	rm *.o
