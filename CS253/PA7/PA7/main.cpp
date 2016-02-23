//Created By Alex Shockency
#include <Image.h>
#include <Interpolation.h>
int Error(char* arg0)
{
	return -1;
}
int main(int argc, char* argv[])
{
	string sLine;	
	if(argc!=4)
	{ 
		cerr << "Usage: " << argv[0] << " filename" << " filename" << "keypoints filename" << endl;
		return Error(argv[0]);
	}
	ifstream istr1(argv[1]);
	if(istr1.fail())
	{
		cerr << "Error: File unreadable" << endl;
		return Error(argv[0]);
	}
	ifstream istr2(argv[2]);
	if(istr2.fail())
	{

		cerr << "Error: File unreadable" << endl;
		return Error(argv[0]);
	}
	ifstream istr3(argv[3]);
	if(istr3.fail())
	{
		cerr << "Error: File unreadable" << endl;
		return Error(argv[0]);
	}
	Image input1;
	if (!input1.magicNumber(istr1))
		return Error(argv[0]);
	Image input2;
	if (!input2.magicNumber(istr2))
		return Error(argv[0]);
	Mapping M1;
	if(!M1.extRead(istr3))
		return Error(argv[0]);
	Morph mor;
	Interpolation I1;
	I1.Interpolate(M1,mor,input1,input2);
}
