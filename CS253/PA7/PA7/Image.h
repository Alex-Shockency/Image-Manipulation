//Created By Alex Shockency
#ifndef Image_H_INCLUDE
#define Image_H_INCLUDE
#include <iostream>
using std::istream;
using std::cout;
using std::cerr;
using std::skipws;
using std::noskipws;
#include <fstream>
using std::ofstream;
using std::ifstream;
#include <sstream>
using std::stringstream;
#include <algorithm>
#include <vector>
using std::vector;
#include <string>
using std::string;
using std::endl;
#include <cmath>
#include <cstring>
using std::strcpy;
//using namespace std;
class Image{
public:
	//Methods
	bool Read(istream& istr);
	bool binaryRead(istream& istr);
	bool magicNumber(istream& istr);
	bool binaryWrite(ofstream& ostr);
	bool Write(ofstream& ostr) const;
	void Min(const Image& Min_in);
	void Max(const Image& Max_in);
	double getAvg(const Image& Avg_in);
	bool reScale(const Image& Re_in);
	bool linearScale(const Image& Lin_in1,const Image& Lin_in2,int N);

	//Accessors
	inline int** getimgVals() const{return imgVals;}
	inline string getFormat() const{return format;}
	inline int getMin() const{return min;}
	inline int getMax() const{return max;}
	inline int getmaxVal() const{return maxVal;}
	inline int getSize() const{return expected_size;}
	inline int getHeight() const{return height;}
	inline int getWidth() const{return width;}

	//Mutators
	inline void setVals (int** newVals){imgVals=newVals;}
	inline void setMin (int newMin){min=newMin;}
	inline void setMax (int newMax){max=newMax;}
	inline void setSize (int newSize){expected_size=newSize;}
	inline void setWidth (int newWidth){width=newWidth;}
	inline void setHeight (int newHeight){height=newHeight;}
	inline void setmaxVal (int newmaxVal){maxVal=newmaxVal;}
	inline void setFormat (string newFormat){format=newFormat;}


private:
	int width;int height;int maxVal;int min;int max;int expected_size;
	string format;
	double avg;
	int** imgVals;
	int* imageValues;
	unsigned char bytes[12];
};
#endif // Image_H_INCLUDE
