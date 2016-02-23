#include <Morph.h>
bool Morph::isKeypoint(int x,int y,vector<Keypoint> keys)
{
	for(unsigned int i=0;i<keys.size();i++)
	{
		if(x==keys[i].getDestX() && y==keys[i].getDestY())
		{
			return true;
		}
	}
	return false;
}
Keypoint Morph::findKeypoint(int x,int y,vector<Keypoint> keys)
{
	for(unsigned int i=0;i<keys.size();i++)
	{
		if(x==keys[i].getDestX() && y==keys[i].getDestY())
		{
			return keys[i];
		}
	}
	return keys[0];
}
int** Morph::Morphing(Image& input,Mapping& map)
{
	int width=input.getWidth();int height=input.getHeight();
	pair <int,int> delta;
	int** inImg=input.getimgVals();	
	vector<Keypoint> keyVec=map.getKey();
	outVals = new int*[width];
	for(int i = 0; i < width; ++i)
	{
		outVals[i] = new int[height];
	}
	for(int y=0; y<height;y++)
	{
		for(int x=0;x<width;x++)
		{
			if(isKeypoint(x,y,keyVec))
			{
				Keypoint key=findKeypoint(x,y,keyVec);
				if(key.getSrcX()>width-1||key.getSrcY()>height-1)
				{
					outVals[x][y]=0;
				}
				else
				outVals [x][y]=inImg[key.getSrcX()][key.getSrcY()];
			}
			else
			{
				delta=map.DeltaXY(x,y);
				int xDel=delta.first;
				int yDel=delta.second;
				if(x-xDel<0||y-yDel<0)
				{
					outVals[x][y]=0;
				}
				else if(x-xDel>width-1||y-yDel>height-1)
				{
					outVals[x][y]=0;
				}
				else
				{
					outVals [x][y]=inImg [x-xDel][y-yDel];
				}
			}
		}
	}
	return outVals;
}
