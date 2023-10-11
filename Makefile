OPLEVEL = -O0

all: dijkstra.o main.o output

output:
	g++ main.o dijkstra.o -o output

main.o: src/main.cpp
	g++ -c $(OPLEVEL) src/main.cpp -o main.o

dijkstra.o: src/dijkstra.cpp includes/dijkstra.h
	g++ -c $(OPLEVEL) src/dijkstra.cpp -o dijkstra.o

