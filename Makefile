OPLEVEL = -O2
MISC_FLAGS = -lpthread -Wall -std=c++11 -pedantic -static-libstdc++ -static-libgcc

all: dijkstra.o main.o output

output: 
	g++ objs/main.o objs/dijkstra.o -o output

main.o: src/main.cpp
	g++ -c $(OPLEVEL) $(MISC_FLAGS) src/main.cpp -o objs/main.o

dijkstra.o: src/dijkstra.cpp includes/dijkstra.h
	g++ -c $(OPLEVEL) $(MISC_FLAGS) src/dijkstra.cpp -o objs/dijkstra.o

