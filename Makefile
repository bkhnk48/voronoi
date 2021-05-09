all: serial

serial:
	g++ -g -c Punto.h
	g++ -g -c Ostacolo.h
	g++ -g -c Voronoi.h
	g++ programma.cpp -g -o out