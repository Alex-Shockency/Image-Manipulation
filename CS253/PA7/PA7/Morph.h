#ifndef Morph_H_INCLUDE
#define Morph_H_INCLUDE
#include <Mapping.h>
#include <Image.h>
class Morph
{
public:
	//Methods
	bool isKeypoint(int x,int y,vector<Keypoint> keys);
	Keypoint findKeypoint(int x,int y,vector<Keypoint> keys);
	int** Morphing(Image& input,Mapping& map);
	//Accesors
	//Mutators
	inline void setOutVals (int** newVals){outVals=newVals;}
private:
	int** outVals;
}
;
#endif // Morph_H_INCLUDE