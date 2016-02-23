#include <Image.h>
//Created By Alex Shockency
bool Image::magicNumber(istream& istr) 
{
	char magNum;
	while(!istr.eof())
	{
		istr >> noskipws >>magNum;
		if(magNum=='P')
		{
			format.append(1,magNum);
			istr >> noskipws >>magNum;
			if(magNum=='2')
			{
				char hashtag;
				string sLine;
				format.append(1,magNum);
				istr >>  hashtag;
				if(isspace(hashtag))
				{ 	
					break;
				}
				else if((hashtag=='#')) 
				{
					getline(istr,sLine);
					break;
				}
				else
				{
					cerr << "Error:  Incorrect magic number format" << endl;
					return false;
				}
			}
			else if(magNum=='5')
			{
				format.append(1,magNum);
				break;
			}
		}
		else
		{
			cerr << "Error:  Incorrect magic number format" << endl;
			return false;
		}
	}	
	if(format=="P2")
	{
		if(!Read(istr)) return false;
		else return true;	
	}	
	else if(format=="P5")
	{
		if(!binaryRead(istr)) return false;
		else return true;
	}
	else
	{
		return false;
	}
}
bool Image::Read (istream& istr) 
{
	char hashtag;
	int count=0;
	string sLine;
	while(true)
	{
		istr >> skipws >> width;
		if(istr.eof())
		{
			break;
		}
		if(istr.fail())
		{
			istr.clear();
			istr >> hashtag;
			if((hashtag=='#')) 
			{
				getline(istr,sLine);
			}
			else
			{
				cerr << "Error: Incorrect format" << endl;
				return false;
			}
		}
		else
		{
			setWidth(width);
			break;
		}
	}
	while(true)
	{
		istr >> skipws >> height;
		if(istr.eof())
		{
			break;
		}
		if(istr.fail())
		{
			istr.clear();
			istr >> hashtag;
			if((hashtag=='#')) 
			{
				getline(istr,sLine);
			}
			else
			{
				cerr << "Error: Incorrect format" << endl;
				return false;
			}
		}
		else
		{
			setHeight(height);
			expected_size=width*height;
			break;
		}
	}
	while(true)
	{
		istr >> skipws >> maxVal;
		if(istr.eof())
		{
			break;
		}
		if(istr.fail())
		{
			istr.clear();
			istr >> hashtag;
			if((hashtag=='#')) 
			{
				getline(istr,sLine);
			}
			else
			{
				cerr << "Error: Incorrect format" << endl;
				return false;
			}
		}
		else
		{
			setmaxVal(maxVal);
			break;
		}
	}
	int** ary =new int*[width];
	for(int i = 0; i < width; i++)
	{
		ary[i] = new int[height];
	}
	for(int y=0;y<height;y++)
	{
		int imgVal;
		for(int x=0;x<width;x++)
		{
			istr >> imgVal;
			if(istr.fail() && !istr.eof())
			{
				istr.clear();
				istr >> hashtag;
				if((hashtag=='#')) 
				{
					getline(istr,sLine);
				}
				else
				{
					cerr << "Error: Invalid pixel value" << endl;
					return false;
				}
			}
			else
			{
				if(imgVal>=0 && imgVal<=255)
				{
					if(imgVal>maxVal)
					{
						cerr << "Error: Pixel value is > max pixel value" << endl;
						return false;	
					}
					ary[x][y]=imgVal;
					count++;
				}
				else
				{
					cerr << "Error: Invalid pixel value" << endl;
					return false;
				}

			}
		}
	}
	setVals(ary);
	if(width<0 || height<0)
	{
		cerr << "Error: Invalid width/height" << endl;
		return false;
	}
	if(!(maxVal<=256 && maxVal>=0))
	{
		cerr << "Error: Max pixel value is invalid" << endl;
		return false;
	}
	if(count>expected_size)
	{
		cerr << "Error: Too many pixel values" << endl;
		return false;	
	}
	else if(count<expected_size)
	{
		cerr << "Error: Too few pixel values" << endl;
		return false;	
	}
	return true;
}
bool Image::binaryRead (istream& istr) 
{
	unsigned char byte;
	int count=0;
	for(int i=0;i<12;i++)
	{
		istr >> byte;
		if(istr.fail())
		{
			return false;
		}
		bytes[i]=byte;
		if(count<4)
		{
			width=(width << 8) + (unsigned int)bytes[i]; 
			count++;
		}
		else if(count<8)
		{
			height=(height << 8) + (unsigned int)bytes[i];
			count++;
		}
		else if(count<12)
		{
			maxVal=(maxVal << 8) + (unsigned int)bytes[i];
			count++;
		}	
	}
	expected_size=width*height;
	int** ary = new int*[width];
	for(int i = 0; i < width; ++i)
	{
		ary[i] = new int[height];
	}
	count=0;
	for(int y=0;y<height;y++)
	{
		int imgVal=0;
		for(int x=0;x<width;x++)
		{
			istr >> byte;
			imgVal=(int)byte;
			if(imgVal>=0 && imgVal<=255)
			{
				if(imgVal>maxVal)
				{
					cerr << "Error: Pixel value is > max pixel value" << endl;
					return false;	
				}
				ary[x][y]=imgVal;
			}
			else
			{
				cerr << "Error: Invalid pixel value" << endl;
				return false;
			}
		}
	}
	setVals(ary);
	if(width<0 || height<0)
	{
		cerr << "Error: Invalid width/height" << endl;
		return false;
	}
	if(!(maxVal<=256 && maxVal>=0))
	{
		cerr << "Error: Max pixel value is invalid" << endl;
		return false;
	}
	if(count>expected_size)
	{
		cerr << "Error: Too many pixel values" << endl;
		return false;	
	}
	else if(count<expected_size)
	{
		cerr << "Error: Too few pixel values" << endl;
		return false;	
	}
	return true;
}

bool Image::Write(ofstream& ostr) const
{
	string magicNum="P2";
	string temp;
	if(ostr.fail()) return false;
	ostr << magicNum << '\n';
	ostr << width << " "<< height <<'\n';
	ostr << maxVal << '\n';
	stringstream out;
	for(int y=0;y<height;y++)
	{	
		for(int x=0;x<width;x++)
		{
			ostr<< imgVals[x][y] <<" ";
		}	
		ostr << '\n';
	}
	return true;	
}
bool Image::binaryWrite(ofstream& ostr) 
{
	string magicNum="P5";
	if(ostr.fail()) return false;
	ostr << magicNum;
	bytes[0] = (width >> 24) & 0xFF;
	bytes[1] = (width >> 16) & 0xFF;
	bytes[2] = (width >> 8) & 0xFF;
	bytes[3] = width & 0xFF;
	bytes[4] = (height >> 24) & 0xFF;
	bytes[5] = (height >> 16) & 0xFF;
	bytes[6] = (height >> 8) & 0xFF;
	bytes[7] = height & 0xFF;
	bytes[8] = (maxVal >> 24) & 0xFF;
	bytes[9] = (maxVal >> 16) & 0xFF;
	bytes[10] = (maxVal >> 8) & 0xFF;
	bytes[11] = maxVal & 0xFF;
	for(unsigned int k=0;k<sizeof(bytes);k++)
	{
		ostr << bytes[k];
	}
	for(int y=0;y<height;y++)
	{	
		for(int x=0;x<width;x++)
		{
			ostr<<(unsigned char)imgVals[x][y];
		}	
	}
	return true;
}
void Image::Max(const Image& Max_in)
{
	max=imgVals[0][0];
	for(int y=0;y<height;y++)
	{
		for(int x=0;x<width;x++)
		{
			if(imgVals[x][y]>max)
			{
				max=imgVals[x][y];
			}
		}
	}
	setMax(max);
}

void Image::Min(const Image& Min_in)
{
	min=imgVals[0][0];
	for(int y=0;y<height;y++)
	{
		for(int x=0;x<width;x++)
		{
			if(imgVals[x][y]<min)
			{
				min=imgVals[x][y];
			}
		}
	}
	setMin(min);
}
double Image::getAvg(const Image& Avg_in)
{
	double sum=0;
	for(int y=0;y<height;y++)
	{
		for(int x=0;x<width;x++)
		{
			sum +=imgVals[x][y];
		}
	}
	avg=sum/expected_size;
	return avg;
}
bool Image::reScale(const Image& Re_in)
{
	setmaxVal(255);
	int** reVals=new int*[width];
	for(int i = 0; i < width; ++i)
	{
		reVals[i] = new int[height];
	}
	double newVal;
	if(max==min)
	{
		return false;
	}
	for(int y=0;y<height;y++)
	{
		for(int x=0;x<width;x++)
		{
			newVal=255*(imgVals[x][y]-min)/(max-min);
			newVal=round(newVal);
			reVals[x][y]=newVal;
		}
	}
	setVals(reVals);
	return true;
}
bool Image::linearScale(const Image& Lin_in1,const Image& Lin_in2,int N)
{
	float k=0;
	double newVal=0;
	string temp;
	char filename[255];
	int** linVals=new int*[width];int** input1=Lin_in1.getimgVals();int** input2=Lin_in2.getimgVals();
	if(Lin_in1.getSize()!=Lin_in2.getSize())
	{
		cerr << "Error: Images do not have same Width & Height" << endl;
		return false;
	}
	for(int i = 0; i < width; ++i)
	{
		linVals[i] = new int[height];
	}
	for(int i=0;i<N+2;i++)
	{
		stringstream out;
		out << i << ".pgm";
		temp=out.str();
		strcpy(filename,temp.c_str());
		ofstream ostr(filename);
		for(int y=0;y<height;y++)
		{
			for(int x=0;x<width;x++)
			{
				newVal=(input1[x][y]+((k/(N+1)))*(input2[x][y]-input1[x][y]));
				newVal=round(newVal);
				linVals[x][y]=newVal;
			}
		}
		k++;
		setVals(linVals);
		if(format=="P2")
		{
			Write(ostr);
		}
		else
		{
			binaryWrite(ostr);
		}
	}
	//memory management
	for (int i = 0; i < width; i++) {
		delete[] linVals[i];
	}
	delete[] linVals;
	for (int i = 0; i < width; i++) {
		delete[] input1[i];
	}
	delete[] input1;
	for (int i = 0; i < width; i++) {
		delete[] input2[i];
	}
	delete[] input2;
	//memory management
	return true;
}
