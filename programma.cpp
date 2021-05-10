/* Created by Simone Tinella, University of Catania*/

#include<iostream>
#include<vector>
#include <fstream>
#include "Voronoi.h"

using namespace std;
int main(){
	int deltaX = 1;
	int deltaY = 1;

	#pragma region first stack
	std::vector<Punto*> quadrato;
	quadrato.push_back(new Punto(10 + deltaX, 10 + deltaY));
	quadrato.push_back(new Punto(10 + deltaX, 28 + deltaY));
	quadrato.push_back(new Punto(80 + deltaX, 28 + deltaY));
	quadrato.push_back(new Punto(80 + deltaX, 10 + deltaY));
	Ostacolo *o=new Ostacolo(&quadrato);		
	#pragma endregion
	
	#pragma region second stack
	std::vector<Punto*> figura;
	figura.push_back(new Punto(10 + deltaX, 38 + deltaY));//R
	figura.push_back(new Punto(10 + deltaX, 50 + deltaY));//S
	figura.push_back(new Punto(12 + deltaX, 50 + deltaY));//T
	figura.push_back(new Punto(12 + deltaX, 56 + deltaY));//U
	figura.push_back(new Punto(80 + deltaX, 56 + deltaY));//V
	figura.push_back(new Punto(80 + deltaX, 38 + deltaY));//W
	Ostacolo *o1=new Ostacolo(&figura);
	#pragma endregion

	#pragma region gate 1
	//left wall near gate 1
	std::vector<Punto*> fboundary11;
	fboundary11.push_back(new Punto(0 + deltaX, 66 + deltaY));
	fboundary11.push_back(new Punto(0 + deltaX, 67 + deltaY));
	fboundary11.push_back(new Punto(36 + deltaX, 67 + deltaY));
	fboundary11.push_back(new Punto(36 + deltaX, 66 + deltaY));
	Ostacolo *o11=new Ostacolo(&fboundary11);
	//Median strip at gate 1
	std::vector<Punto*> fboundary12;
	fboundary12.push_back(new Punto(44 + deltaX, 67 + deltaY));
	fboundary12.push_back(new Punto(46 + deltaX, 67 + deltaY));
	fboundary12.push_back(new Punto(46 + deltaX, 66 + deltaY));
	fboundary12.push_back(new Punto(44 + deltaX, 66 + deltaY));
	Ostacolo *o12 = new Ostacolo(&fboundary12);
	//right wall near gate 1
	std::vector<Punto*> fboundary13;
	fboundary13.push_back(new Punto(54 + deltaX, 66 + deltaY));
	fboundary13.push_back(new Punto(54 + deltaX, 67 + deltaY));
	fboundary13.push_back(new Punto(90 + deltaX, 67 + deltaY));
	fboundary13.push_back(new Punto(90 + deltaX, 66 + deltaY));
	Ostacolo *o13=new Ostacolo(&fboundary13);
	#pragma endregion
	
	#pragma region gate 4
	//left wall near gate 4
	std::vector<Punto*> fboundary41;
	fboundary41.push_back(new Punto(-1 + deltaX, 0 + deltaY));
	fboundary41.push_back(new Punto(-1 + deltaX, 24 + deltaY));
	fboundary41.push_back(new Punto(0 + deltaX, 24 + deltaY));
	fboundary41.push_back(new Punto(0 + deltaX, 0 + deltaY));
	Ostacolo *o41 = new Ostacolo(&fboundary41);

	//right wall near gate 4
	std::vector<Punto*> fboundary43;
	fboundary43.push_back(new Punto(-1 + deltaX, 42 + deltaY));
	fboundary43.push_back(new Punto(-1 + deltaX, 66 + deltaY));
	fboundary43.push_back(new Punto(0 + deltaX, 66 + deltaY));
	fboundary43.push_back(new Punto(0 + deltaX, 42 + deltaY));
	Ostacolo *o43 = new Ostacolo(&fboundary43);

	//median strip near gate 4
	std::vector<Punto*> fboundary42;
	fboundary42.push_back(new Punto(-1 + deltaX, 32 + deltaY));
	fboundary42.push_back(new Punto(-1 + deltaX, 34 + deltaY));
	fboundary42.push_back(new Punto(0 + deltaX, 34 + deltaY));
	fboundary42.push_back(new Punto(0 + deltaX, 32 + deltaY));
	Ostacolo *o42 = new Ostacolo(&fboundary42);
	#pragma endregion

	std::vector<Punto*> fboundary3;
	fboundary3.push_back(new Punto(90 + deltaX, 0 + deltaY));
	fboundary3.push_back(new Punto(90 + deltaX, 66 + deltaY));
	fboundary3.push_back(new Punto(91 + deltaX, 66 + deltaY));
	fboundary3.push_back(new Punto(91 + deltaX, 0 + deltaY));
	Ostacolo *o4 = new Ostacolo(&fboundary3);

	#pragma region gate 3
	//left wall near gate 3
	std::vector<Punto*> fboundary31;
	fboundary31.push_back(new Punto(0 + deltaX, 0 + deltaY));
	fboundary31.push_back(new Punto(36 + deltaX, 0 + deltaY));
	fboundary31.push_back(new Punto(36 + deltaX, -1 + deltaY));
	fboundary31.push_back(new Punto(-1 + deltaX, -1 + deltaY));
	Ostacolo *o31 = new Ostacolo(&fboundary31);

	//right wall near gate 3
	std::vector<Punto*> fboundary33;
	fboundary33.push_back(new Punto(54 + deltaX, 0 + deltaY));
	fboundary33.push_back(new Punto(90 + deltaX, 0 + deltaY));
	fboundary33.push_back(new Punto(90 + deltaX, -1 + deltaY));
	fboundary33.push_back(new Punto(54 + deltaX, -1 + deltaY));
	Ostacolo *o33 = new Ostacolo(&fboundary33);

	//Median strip at gate 3
	std::vector<Punto*> fboundary32;
	fboundary32.push_back(new Punto(44 + deltaX, 0 + deltaY));
	fboundary32.push_back(new Punto(46 + deltaX, 0 + deltaY));
	fboundary32.push_back(new Punto(46 + deltaX, -1 + deltaY));
	fboundary32.push_back(new Punto(44 + deltaX, -1 + deltaY));
	Ostacolo *o32 = new Ostacolo(&fboundary32);
	#pragma endregion

	std::vector<Ostacolo*> ostacoli;
	ostacoli.push_back(o);
	ostacoli.push_back(o1);

	ostacoli.push_back(o11);
	ostacoli.push_back(o12);
	ostacoli.push_back(o13);

	ostacoli.push_back(o41);
	ostacoli.push_back(o42);
	ostacoli.push_back(o43);

	ostacoli.push_back(o4);
	ostacoli.push_back(o31);
	ostacoli.push_back(o32);
	ostacoli.push_back(o33);
	
	Voronoi *mappa=new Voronoi(200,200,ostacoli);
	std::vector<Punto*> *voronoi= mappa->getPuntiVoronoi();
	ostacoli= *mappa->getOstacoli();
	std::vector<Punto*> *incroci= mappa->getIncroci();
	
	Punto *partenza= new Punto(11 + deltaX, 53 + deltaY);
	Punto *arrivo= new Punto(39 + deltaX, 0 + deltaY);
	std::vector<Punto> percorso=mappa->getPercorso(*partenza,*arrivo);
	
	std::ofstream fostacoli("ostacoli.txt");
	for(int i=0;i<ostacoli.size();i++){
		for(int j=0;j<ostacoli.at(i)->getEdges()->size();j++){
		fostacoli<< ostacoli.at(i)->getEdges()->at(j)->getX()
				<< " " << ostacoli.at(i)->getEdges()->at(j)->getY() << std::endl;
		}
	}
	fostacoli.close();
	
	std::ofstream fvoronoi("voronoi.txt");
	for(int i=0;i<voronoi->size();i++){
		fvoronoi<< voronoi->at(i)->getX() << " " << voronoi->at(i)->getY() << std::endl;		
	}
	fvoronoi.close();
	
	std::ofstream fpercorso("percorso.txt");
	for(int i=0;i<percorso.size();i++){
		fpercorso<< percorso.at(i).getX() << " " << percorso.at(i).getY() << std::endl;		
	}
	fpercorso.close();
	
	std::ofstream fincroci("incroci.txt");
	for(int i=0;i<incroci->size();i++){
		fincroci<< incroci->at(i)->getX() << " " << incroci->at(i)->getY() << std::endl;		
	}
	fincroci.close();
}