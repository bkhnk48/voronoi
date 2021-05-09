/* Created by Simone Tinella, University of Catania*/

#include<iostream>
#include<vector>
#include <fstream>
#include "Voronoi.h"

using namespace std;
int main(){
	int deltaX = 1;
	int deltaY = 1;
	std::vector<Punto*> quadrato;
	quadrato.push_back(new Punto(10 + deltaX, 10 + deltaY));
	quadrato.push_back(new Punto(10 + deltaX, 28 + deltaY));
	quadrato.push_back(new Punto(80 + deltaX, 28 + deltaY));
	quadrato.push_back(new Punto(80 + deltaX, 10 + deltaY));
	Ostacolo *o=new Ostacolo(&quadrato);		
	
	std::vector<Punto*> figura;
	figura.push_back(new Punto(10 + deltaX, 38 + deltaY));//R
	figura.push_back(new Punto(10 + deltaX, 50 + deltaY));//S
	figura.push_back(new Punto(12 + deltaX, 50 + deltaY));//T
	figura.push_back(new Punto(12 + deltaX, 56 + deltaY));//U
	figura.push_back(new Punto(80 + deltaX, 56 + deltaY));//V
	figura.push_back(new Punto(80 + deltaX, 38 + deltaY));//W
	Ostacolo *o1=new Ostacolo(&figura);

	std::vector<Punto*> fboundary1;
	fboundary1.push_back(new Punto(0 + deltaX, 66 + deltaY));//R
	fboundary1.push_back(new Punto(90 + deltaX, 66 + deltaY));//S
	fboundary1.push_back(new Punto(90 + deltaX, 67 + deltaY));//T
	fboundary1.push_back(new Punto(0 + deltaX, 67 + deltaY));//U
	Ostacolo *o2=new Ostacolo(&fboundary1);

	std::vector<Punto*> fboundary2;
	fboundary2.push_back(new Punto(-1 + deltaX, 0 + deltaY));//R
	fboundary2.push_back(new Punto(-1 + deltaX, 66 + deltaY));//S
	fboundary2.push_back(new Punto(0 + deltaX, 66 + deltaY));//T
	fboundary2.push_back(new Punto(0 + deltaX, 0 + deltaY));//U
	Ostacolo *o3 = new Ostacolo(&fboundary2);

	std::vector<Punto*> fboundary3;
	fboundary3.push_back(new Punto(90 + deltaX, 0 + deltaY));//R
	fboundary3.push_back(new Punto(90 + deltaX, 66 + deltaY));//S
	fboundary3.push_back(new Punto(91 + deltaX, 66 + deltaY));//T
	fboundary3.push_back(new Punto(91 + deltaX, 0 + deltaY));//U
	Ostacolo *o4 = new Ostacolo(&fboundary3);

	std::vector<Punto*> fboundary4;
	fboundary4.push_back(new Punto(0 + deltaX, 0 + deltaY));//R
	fboundary4.push_back(new Punto(36 + deltaX, 0 + deltaY));//S
	fboundary4.push_back(new Punto(36 + deltaX, -1 + deltaY));//T
	fboundary4.push_back(new Punto(-1 + deltaX, -1 + deltaY));//U
	Ostacolo *o5 = new Ostacolo(&fboundary4);

	std::vector<Punto*> fboundary5;
	fboundary5.push_back(new Punto(54 + deltaX, 0 + deltaY));//R
	fboundary5.push_back(new Punto(90 + deltaX, 0 + deltaY));//S
	fboundary5.push_back(new Punto(90 + deltaX, -1 + deltaY));//T
	fboundary5.push_back(new Punto(54 + deltaX, -1 + deltaY));//U
	Ostacolo *o6 = new Ostacolo(&fboundary5);

	std::vector<Ostacolo*> ostacoli;
	ostacoli.push_back(o);
	ostacoli.push_back(o1);
	ostacoli.push_back(o2);
	ostacoli.push_back(o3);
	ostacoli.push_back(o4);
	ostacoli.push_back(o5);
	ostacoli.push_back(o6);
	
	cout << "Here 1" <<endl;
	Voronoi *mappa=new Voronoi(200,200,ostacoli);
	std::vector<Punto*> *voronoi= mappa->getPuntiVoronoi();
	ostacoli= *mappa->getOstacoli();
	std::vector<Punto*> *incroci= mappa->getIncroci();
	
	Punto *partenza= new Punto(11 + deltaX, 53 + deltaY);
	Punto *arrivo= new Punto(39 + deltaX, 0 + deltaY);
	std::vector<Punto> percorso=mappa->getPercorso(*partenza,*arrivo);
	
	cout << "Here" <<endl;
	std::ofstream fostacoli("ostacoli.txt");
	for(int i=0;i<ostacoli.size();i++){
		for(int j=0;j<ostacoli.at(i)->getIngombro()->size();j++){
		fostacoli<< ostacoli.at(i)->getIngombro()->at(j)->getX() << " " << ostacoli.at(i)->getIngombro()->at(j)->getY() << std::endl;
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