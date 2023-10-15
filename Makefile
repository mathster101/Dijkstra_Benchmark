OPLEVEL = -O2
MISC_FLAGS = -lpthread -Wall

all: dijkstra.o main.o output

output: 
	g++ main.o dijkstra.o -o output

main.o: src/main.cpp
	g++ -c $(OPLEVEL) src/main.cpp -o main.o

dijkstra.o: src/dijkstra.cpp includes/dijkstra.h
	g++ -c $(OPLEVEL) $(MISC_FLAGS) src/dijkstra.cpp -o dijkstra.o

