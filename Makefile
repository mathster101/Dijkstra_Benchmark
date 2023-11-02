OPLEVEL = -O2
MISC_FLAGS = -lpthread -Wall -std=c++11 -pedantic #-static-libstdc++ -static-libgcc

all: dijkstra.o main.o output

output: 
	g++ objs/main.o objs/dijkstra.o -o output $(MISC_FLAGS) $(OPLEVEL)

main.o: src/main.cpp
	g++ -c src/main.cpp -o objs/main.o $(OPLEVEL) $(MISC_FLAGS)

dijkstra.o: src/dijkstra.cpp includes/dijkstra.h
	g++ -c src/dijkstra.cpp -o objs/dijkstra.o $(OPLEVEL) $(MISC_FLAGS)

