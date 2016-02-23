#ifndef Coordinate_H_INCLUDE
#define Coordinate_H_INCLUDE
#include <utility>
using std::pair;
class Coordinate{
public:
	//Accessors
	inline int getX() const{return xy.first;}
	inline int getY() const{return xy.second;}
	//Mutators
	inline void setX (int newX){xy.first=newX;}
	inline void setY (int newY){xy.second=newY;}
private:
	pair <int,int> xy;
};
#endif // Coordinate_H_INCLUDE