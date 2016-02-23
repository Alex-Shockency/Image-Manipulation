#include <Mapping.h>
bool Mapping::Read(istream& istr)
{
	Keypoint K1;
	vector<Keypoint> keyVec;
	int x1;int y1;int x2;int y2;int temp;int err=1;
	string sLine;
	while(true)
	{
		if(istr.eof())
		{
			break;
		}
		getline(istr,sLine);
		std::istringstream ss(sLine);
		if(sLine.empty())
		{
			if(err==1)
			{
				cerr << "Error: Invalid line format on line " << err << endl;
				return false;
			}
			else 
				continue;
		}
		ss >> x1 >> y1 >> x2 >> y2;
		if(ss.fail())
		{
			cerr << "Error: Invalid line format on line " << err << endl;
			return false;
		}
		ss >> temp;
		if(ss.fail() && ss.eof())
		{
			K1.setSrcX(x1);K1.setSrcY(y1);K1.setDestX(x2);K1.setDestY(y2);K1.setDiffX(x2-x1);K1.setDiffY(y2-y1);
			keyVec.push_back(K1);
		}
		else
		{
			cerr << "Error: Invalid line format on line " << err << endl;
			return false;
		}
		setKey(keyVec);
		err++;
	}
	return true;
}
bool Mapping::extRead(istream& istr)
{
	Coordinate co;
	int x=0;int y=0;int temp=0;int count=0;int err=0;
	vector<Coordinate> coors;
	vector<vector<Coordinate> > points;
	string sLine;
	while(getline(istr,sLine))
	{
		std::istringstream ss(sLine);
		if(sLine.empty())
		{
			if(err==1)
			{
				cerr << "Error: Invalid line format on line " << err << endl;
				return false;
			}
			else 
				continue;
		}
        while(ss >>x >> y)
		{
			co.setX(x);
			co.setY(y);
			coors.push_back(co);
			temp++;
		}
		points.push_back(coors);
		if(count==0)
		{
		setN(temp-2);
		}
		if(temp-2!=getN())
		{
			cerr << "Error: Not enough intermediate values " << err << endl;
			return false;
		}
		temp=0;
		coors.clear();
		count++;
	}
	setKeys(points);
	return true;
}
bool Mapping::srcMaker(int j)
{
	Keypoint K1;
	vector<Keypoint> keyVec;
	for(unsigned int i=0;i<keys.size();i++)
	{
	K1.setSrcX(keys[i][0].getX());
	K1.setSrcY(keys[i][0].getY());
	K1.setDestX(keys[i][j].getX());
	K1.setDestY(keys[i][j].getY());
	K1.setDiffX(keys[i][j].getX()-keys[i][0].getX());
	K1.setDiffY(keys[i][j].getY()-keys[i][0].getY());
	keyVec.push_back(K1);
	}
	setKey(keyVec);
	return true;
}
bool Mapping::destMaker(int j)
{
	Keypoint K1;
	vector<Keypoint> keyVec;
	for(unsigned int i=0;i<keys.size();i++)
	{
	K1.setSrcX(keys[i][keys[0].size()-1].getX());
	K1.setSrcY(keys[i][keys[0].size()-1].getY());
	K1.setDestX(keys[i][j].getX());
	K1.setDestY(keys[i][j].getY());
	K1.setDiffX(keys[i][j].getX()-keys[i][keys[0].size()-1].getX());
	K1.setDiffY(keys[i][j].getY()-keys[i][keys[0].size()-1].getY());
	keyVec.push_back(K1);
	}
	setKey(keyVec);
	return true;
}
double Mapping::Weight(int x,int y, int kindex)
{
	double weight;
	int xk=keypoints[kindex].getDestX();
	int yk=keypoints[kindex].getDestY();
	double denom=pow(x-xk,2)+pow(y-yk,2);
	weight=1/denom;
	return weight;
}
pair<int,int> Mapping::DeltaXY(int x,int y)
{
	pair <int,int> delta;
	double result=0;
	double numX=0;
	double numY=0;
	double denom=0;
	for(unsigned int i=0;i<keypoints.size();i++)
	{
		numX+=Weight(x,y,i)*(keypoints[i].getDiffX());
		numY+=Weight(x,y,i)*keypoints[i].getDiffY();
		denom+=Weight(x,y,i);
	}
	result=(numX/denom);
	result=round(result);
	delta.first=result;
	result=(numY/denom);
	result=round(result);
	delta.second=result;
	return delta;
}