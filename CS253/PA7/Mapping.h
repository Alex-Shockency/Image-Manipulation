#ifndef Mapping_H_INCLUDE
#define Mapping_H_INCLUDE
#include <Keypoint.h>
#include <Coordinate.h>
#include <iostream>
using std::istream;
using std::cout;
using std::cerr;
#include <sstream>
using std::stringstream;
#include <algorithm>
#include <vector>
using std::vector;
#include <string>
using std::string;
using std::endl;
using std::to_string;
#include <cmath>
#include <utility>
using std::pair;
class Mapping
{
public:
	//Methods
	bool Read(istream& istr);
	bool srcMaker(int j);
	bool destMaker(int j);
	bool extRead(istream& istr);
	double Weight(int x,int y,int kindex);
	pair <int,int> DeltaXY(int x,int y);
	//Accesors
	inline vector <Keypoint> getKey() const{return keypoints;}
	inline vector<vector<Coordinate> >getKeys() const{return keys;}
	inline double getN() const{return N;}
	//Mutators
	inline void setKey (vector <Keypoint> newKey){keypoints=newKey;}
	inline void setKeys (vector<vector<Coordinate> > newKeys){keys=newKeys;}
	inline void setN (double newN){N=newN;}
private:
	vector<vector<Coordinate> > keys;
	double N;
	vector <Keypoint> keypoints;
};
#endif // Mapping_H_INCLUDE
