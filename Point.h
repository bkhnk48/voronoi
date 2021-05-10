/* Created by Simone Tinella, University of Catania
 * Edited by ThanhNT
*/

class Point{
	private:
		double x,y;
	public:
		Point(double x,double y);
		double getX();
		double getY();
};

Point::Point(double x,double y){
	this->x=x;
	this->y=y;
}

double Point::getX(){
	return x;
}

double Point::getY(){
	return y;
}
