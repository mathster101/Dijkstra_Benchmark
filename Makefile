all: dijkstra_file

dijkstra_file: src/dijkstra.cpp includes/dijkstra.h
	g++ -c src/dijkstra.cpp -o dijkstra.o