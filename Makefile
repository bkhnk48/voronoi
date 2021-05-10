all: serial

serial:
	g++ -g -c Point.h
	g++ -g -c Ostacolo.h
	g++ -g -c Voronoi.h
	g++ programma.cpp -g -o out
clean: 
	-rm *.o
	-rm *.txt
	-rm out
	-rm *.gch
clear: 
	-rm *.o
	-rm *.txt
	-rm out
	-rm *.gch
c: 
	-rm *.o
	-rm *.txt
	-rm out
	-rm *.gch