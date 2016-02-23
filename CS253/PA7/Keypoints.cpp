#include <Mapping.h>
bool Keypoints::Read(istream& istr)
{
	int x1;
	int y1;
	int x2;
	int y2;
	int temp;
	int err=1;
	string sLine;
	while(true)
	{
		if(istr.eof())
		{
			break;
		}
		getline(istr,sLine);
		std::istringstream ss(sLine);
		ss >> x1 >> y1 >> x2 >> y2;
		cout << x1 << endl;
		if(ss.fail())
		{
			cerr << "Error: Invalid line format on line " << err << endl;
			return false;
			
		}
		ss >> temp;
		if(ss.fail() && ss.eof())
		{
			setSrcX(x1);
			setSrcY(y1);
			setDestX(x2);
			setDestY(y2);
			setDiffX(x2-x1);
			setDiffY(y2-y1);
		}
		else
		{
			cerr << "Error: Invalid line format on line " << err << endl;
			return false;
		}
		err++;
	}
	return true;
}