/* Created by Simone Tinella, University of Catania*/

#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>
#include "Polygon.h"

const double unit= 1;
const double raggio_ricerca = 5*unit*sqrt(2); //raggio ricerca vicini
const double dist_tolleranza= unit*sqrt(2);

const double distanza= 5*unit;//*sqrt(2); //filtro
const int scarto=1; //filtro

class Voronoi{
	private:
		double lunghezza;
		double larghezza;
		std::vector<Polygon*> polygon;
		std::vector<Point*> point_voronoi;
		std::vector<Point*> incroci;
		void CreaVoronoi();
		std::vector<Point*> getPercorsoVoronoi(Point partenza,Point arrivo,std::vector<Point*> *incroci_s);
		std::vector<Point*> getPercorsoVoronoi2(Point partenza,Point arrivo);
		bool inPolygon(double X, double Y);
				
	public:
		Voronoi(double larghezza,double lunghezza,std::vector<Polygon*> ostacoli);
		std::vector<Polygon*> *getPolygon();
		std::vector<Point*> *getPointVoronoi();
		std::vector<Point> getPercorso(Point partenza,Point arrivo);
		Point getPointDistanzaMinima(Point p);	
		std::vector<Point*> *getIncroci();
		
};

Voronoi::Voronoi(double larghezza,double lunghezza,std::vector<Polygon*> ostacoli){
	this->polygon = ostacoli;
	
	//Usare questo se non si vogliono i collegamenti degli spiegoli dell'ambiente
	std::vector<Point*> ambiente;
	ambiente.push_back(new Point(0,0));
	ambiente.push_back(new Point(larghezza-1,0));
	ambiente.push_back(new Point(larghezza-1,lunghezza-1));
	ambiente.push_back(new Point(0,lunghezza-1));
	//this->polygon.push_back(new Polygon(&ambiente));//tu y set comment
	
	//usare questo se si vogliono gli spigoli dell'ambiente
	/*std::vector<Point*> ambiente;
	ambiente.push_back(new Point(0,0));
	ambiente.push_back(new Point(larghezza-1,0));
	this->ostacoli.push_back(new Ostacolo(&ambiente));
	std::vector<Point*> ambiente2;
	ambiente2.push_back(new Point(larghezza-1,1));
	ambiente2.push_back(new Point(larghezza-1,lunghezza-1));
	this->ostacoli.push_back(new Ostacolo(&ambiente2));
	std::vector<Point*> ambiente3;
	ambiente3.push_back(new Point(larghezza-2,lunghezza-1));
	ambiente3.push_back(new Point(0,lunghezza-1));
	this->ostacoli.push_back(new Ostacolo(&ambiente3));
	std::vector<Point*> ambiente4;
	ambiente4.push_back(new Point(0,lunghezza-2));
	ambiente4.push_back(new Point(0,1));
	this->ostacoli.push_back(new Ostacolo(&ambiente4));*/
	
	this->lunghezza=lunghezza;
	this->larghezza=larghezza;
	
	std::cout<<"I am looking for the points of voronoi"<<std::endl;
	CreaVoronoi();
	std::cout<<"Voronoi map created"<<std::endl;
}

std::vector<Polygon*> *Voronoi::getPolygon(){
	return &polygon;
}

std::vector<Point*> *Voronoi::getPointVoronoi(){
	return &point_voronoi;
}

std::vector<Point*> *Voronoi::getIncroci(){
	return &incroci;
}

bool Voronoi::inPolygon(double X, double Y){
	for(int p = 0; p < polygon.size(); p++){
		int nVert = polygon.at(p)->vertices.size();
		int i, j, c = 0;
		for(i = 0, (j = nVert - 1); i < nVert; j = i++)
		{
			double vertxI = polygon.at(p)->vertices.at(i)->getX();
			double vertyI = polygon.at(p)->vertices.at(i)->getY();
			double vertxJ = polygon.at(p)->vertices.at(j)->getX();
			double vertyJ = polygon.at(p)->vertices.at(j)->getY();
			if(((vertyI > Y) != (vertyJ > Y)) &&
     			(X < (vertxJ - vertxI) * (Y - vertyI) / (vertyJ-vertyI) + vertxI) )
       			c = !c;
  		}
		if(c == 1)
  			return true;
	}
	return false;
}

void Voronoi::CreaVoronoi(){
	
	for(double tmpY = unit; tmpY < lunghezza - unit; tmpY += unit){
		
		float percento = ((float)tmpY/(float)(lunghezza-unit))*100;
		std::cout<<"Processing: "<<percento<<"% \r";
		//std::cout<<"Loops: "<<larghezza-unit<<"!"<<std::endl;
		for(double tmpX = unit;tmpX < larghezza-unit; tmpX += unit){
		
			if(!inPolygon(tmpX, tmpY)){
				Point *tmp_Point= new Point(tmpX,tmpY);
				
				std::vector<double> distance;
				for(int i = 0;i < polygon.size();i++){
					double minDist = 10000;
					for(int j=0;j < polygon.at(i)->getEdges()->size();j++){
						double tmp_dist= Polygon::Distance(*tmp_Point,*polygon.at(i)->getEdges()->at(j));
						//double tmp_dist= fabs(tmp_Point->getX()-ostacoli.at(i)->getIngombro()->at(j)->getX())+fabs(tmp_Point->getY()-ostacoli.at(i)->getIngombro()->at(j)->getY());
						if(tmp_dist < minDist) 
							minDist=tmp_dist;
					}
					distance.push_back(minDist);
				}
				
				//Mi servono le distanze dagli ostacoli + vicini
				std::sort(distance.begin(),distance.begin()+distance.size());
				
				double min1= distance.at(0);
				double min2= distance.at(1);	
				
				if(fabs(min2-min1) <= dist_tolleranza){
					point_voronoi.push_back(tmp_Point);
					
					if(polygon.size()>2){
						double min3= distance.at(2);
						if(fabs(min2-min3) <= dist_tolleranza && fabs(min3-min1) <= dist_tolleranza) 
							incroci.push_back(tmp_Point);	
					}
					
				}else delete tmp_Point;
		
			}
		}
	}
}



std::vector<Point> Voronoi::getPercorso(Point partenza,Point arrivo){
	std::cout<<"I calculate the route"<<std::endl;
	
	std::vector<Point> percorso;
	percorso.push_back(partenza); //solo temporaneo
	double dist = 10000;
	double dist2 = 10000;
	Point *minimo_arrivo = NULL;
	Point *minimo = NULL;
	
	for(int i=0; i < point_voronoi.size(); i++){
		Point *p = point_voronoi.at(i);
		//std::cout<<"(X = "<<p->getX()<<" "<<"Y = "<<p->getY()<<") ";
		double val = sqrt((partenza.getX()-p->getX())*(partenza.getX()-p->getX()) + (partenza.getY()-p->getY())*(partenza.getY()-p->getY()));
        double val2 = sqrt((arrivo.getX()-p->getX())*(arrivo.getX()-p->getX()) + (arrivo.getY()-p->getY())*(arrivo.getY()-p->getY()));
		if(val < dist){
			minimo=p;
			dist=val;
		}
		if(val2 < dist2){
			minimo_arrivo=p;
			dist2=val2;
		}
	}
	
	if(minimo == NULL) return percorso;
	if(minimo_arrivo == NULL) return percorso;
	
	percorso.push_back(*minimo);
	
	if(minimo->getX() == arrivo.getX() && minimo->getY() == arrivo.getY()) 
		return percorso;
	
	std::vector<Point*> perc_voro= getPercorsoVoronoi(*minimo,*minimo_arrivo,NULL);
	//std::vector<Point*> perc_voro= getPercorsoVoronoi2(*minimo,*minimo_arrivo);
	
	if(perc_voro.size()>0){
		Point *tmp=perc_voro.at(0);
		percorso.push_back(*tmp);
		for(int i = 1; i < perc_voro.size(); i++){
			if(Polygon::Distance(*tmp,*perc_voro.at(i)) >= distanza){
				percorso.push_back(*perc_voro.at(i));
				tmp=perc_voro.at(i);
			}
		}
		
		std::vector<Point> temp;
		for(int i = 0;i < percorso.size(); i += scarto){
			temp.push_back(percorso.at(i));
		}
		percorso=temp;
			
	}
	
	percorso.push_back(*minimo_arrivo);
	percorso.push_back(arrivo);
	
	return percorso;	
}



std::vector<Point*> Voronoi::getPercorsoVoronoi(Point partenza,Point arrivo,std::vector<Point*> *incroci_s){
	std::vector<Point*> percorso;
	std::vector<Point*> punti_passati;
	punti_passati.push_back(&partenza);
	
	Point *tmp=&partenza;
	int n = 0;
	
	do{
		std::vector<Point*> vicini;
		
		for(int i = 0;i < point_voronoi.size();i++){
			Point *p = point_voronoi.at(i);
			double val= sqrt((tmp->getX()-p->getX())*(tmp->getX()-p->getX()) + (tmp->getY()-p->getY())*(tmp->getY()-p->getY()));
			
			bool passato=false;
			for(int i=0;i<punti_passati.size();i++){
				if(p==punti_passati.at(i))
					passato=true;
			}
			
			if(val <=raggio_ricerca && !passato)
				vicini.push_back(p);
		}
		
		if(vicini.size() > 0){
			double dist = 10000;
			Point *temp;
			for(int i = 0; i < vicini.size(); i++){
				Point *vicino = vicini.at(i);
				double val = sqrt((vicino->getX()-arrivo.getX())*(vicino->getX()-arrivo.getX()) + (vicino->getY()-arrivo.getY())*(vicino->getY()-arrivo.getY()));
				if(val < dist){
					temp = vicino;
					dist = val;
				}
			}
			
			if(dist < Polygon::Distance(*tmp,arrivo)) //controllo per evitare l'allontamento
				tmp = temp;
				else goto alternativo;
				
			//	tmp=temp; //oppure questa senza il controllo di sopra
			percorso.push_back(tmp);
			punti_passati.push_back(tmp);
		}else{
			alternativo:
			std::cout<<"I have not succeeded, I try again"<<std::endl;
		
			percorso.clear();
			punti_passati.clear();
			Point *incrocio_vicino=NULL;
			
			double dist = 10000;
			for(int i = 0; i < incroci.size(); i++){
				Point *inc = incroci.at(i);
				double val = Polygon::Distance(*inc,arrivo);				
				bool presente = false;
				if(incroci_s != NULL)
				for(int j = 0;j < incroci_s->size(); j++){
					if(inc == incroci_s->at(j)){
						presente = true;
						break;
					}						
				}				
				if(val < dist && !presente){
					incrocio_vicino = inc;
					dist = val;
				} 				
			}
			
			if(incrocio_vicino == NULL) {
				std::cout<<"Could not find a path"<<std::endl;
				exit(-1);
			}
			
 			std::cout<<"Close chosen intersection: "<<incrocio_vicino->getX()<<" "<<incrocio_vicino->getY();
			
			if(incroci_s == NULL){
				std::vector<Point*> incroci_scelti;
				incroci_s=&incroci_scelti;				
			}
			
			incroci_s->push_back(incrocio_vicino);
			percorso = getPercorsoVoronoi(partenza,*incrocio_vicino,incroci_s);
			
			std::vector<Point*> restante = getPercorsoVoronoi(*incrocio_vicino,arrivo,incroci_s); 
			
			percorso.insert(percorso.end(),restante.begin(),restante.end());
			return percorso;
		}
		
		
		n++;
	}while(!(tmp->getX() == arrivo.getX() && tmp->getY() == arrivo.getY()));
	//std::cout<<"n = "<<n<<std::endl;
	
	return percorso;
}

std::vector<Point*> Voronoi::getPercorsoVoronoi2(Point partenza,Point arrivo){
	std::vector<Point*> percorso;
	
	Point *incrocio_partenza;
	Point *incrocio_arrivo;
	
	double dist1=10000;
	double dist2=10000;
	for(int i=0;i<incroci.size();i++){
		Point *inc= incroci.at(i);
		double val= Polygon::Distance(*inc,partenza);
		double val2= Polygon::Distance(*inc,arrivo);		
		if(val<dist1){
			dist1=val;
			incrocio_partenza=inc;
		}
		if(val2<dist2){
			dist2=val2;
			incrocio_arrivo=inc;
		}		
	}
	
	dist1 = 10000;
	Point *incrocio_obiettivo;
	for(int i = 0;i < incroci.size(); i++){
		Point *inc = incroci.at(i);
		double val = Polygon::Distance(*inc,*incrocio_partenza);
		double val2 = Polygon::Distance(*inc,*incrocio_arrivo);
		if(fabs(val-val2) < dist1){
			incrocio_obiettivo = inc;
			dist1 = fabs(val-val2);
		}	
	}
	
	percorso = getPercorsoVoronoi(partenza,*incrocio_arrivo,NULL);
	
	std::vector<Point*> temp;/*= getPercorsoVoronoi(*incrocio_partenza,*incrocio_obiettivo,NULL);
	percorso.insert(percorso.end(),temp.begin(),temp.end());
	
	temp= getPercorsoVoronoi(*incrocio_obiettivo,*incrocio_arrivo,NULL);
	percorso.insert(percorso.end(),temp.begin(),temp.end());*/
	
	temp = getPercorsoVoronoi(*incrocio_arrivo,arrivo,NULL);
	percorso.insert(percorso.end(),temp.begin(),temp.end());
	
	return percorso;
}




