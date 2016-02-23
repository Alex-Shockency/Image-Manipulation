#ifndef Keypoint_H_INCLUDE
#define Keypoint_H_INCLUDE

class Keypoint{
public:
	//Accessors
	inline int getSrcX() const{return srcX;}
	inline int getSrcY() const{return srcY;}
	inline int getDestX() const{return destX;}
	inline int getDestY() const{return destY;}
	inline int getDiffX() const{return diffX;}
	inline int getDiffY() const{return diffY;}
	//Mutators
	inline void setSrcX (int newSrcX){srcX=newSrcX;}
	inline void setSrcY (int newSrcY){srcY=newSrcY;}
	inline void setDestX (int newDestX){destX=newDestX;}
	inline void setDestY (int newDestY){destY=newDestY;}
	inline void setDiffX (int newDiffX){diffX=newDiffX;}
	inline void setDiffY (int newDiffY){diffY=newDiffY;}
private:
	int srcX;
	int srcY;
	int destX;
	int destY;
	int diffX;
	int diffY;
};
#endif // Keypoint_H_INCLUDE