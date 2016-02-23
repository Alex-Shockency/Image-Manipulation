#include <Interpolation.h>
bool Interpolation::Interpolate(Mapping& map,Morph& mor,Image& img1,Image& img2)
{
    Image output;
   	double N=map.getN();double newVal;double firstHalf;double secondHalf;double J=1;
   	int width=img1.getWidth();int height=img1.getHeight();
    int **srcPixels;int **destPixels;int** interVals=new int*[width];
    //for memory management
     int**imgVals1=img1.getimgVals();int**imgVals2=img2.getimgVals();
    /////////////////////////////////////////////////////////////////
    //intialize output image
    output.setWidth(width);
    output.setHeight(height);
    output.setmaxVal(img1.getmaxVal());
    output.setSize(img1.getSize());
    ///////////////////////////////
    char filename[255];
    string temp;
    for(int i = 0; i < width; ++i)
    {
        interVals[i] = new int[height];
    }
    for(int j=1;j<=N;j++)
    {
        stringstream out;
        out << j << ".pgm";
        temp=out.str();
        strcpy(filename,temp.c_str());
        ofstream ostr(filename);
        //intialize source pixels
        map.srcMaker(j);
        srcPixels=mor.Morphing(img1,map);
        //intialize dest pixels
        map.destMaker(j);
        destPixels=mor.Morphing(img2,map);
        //////////////////////////////////
        for(int y=0;y<height;y++)
        {
        	for(int x=0;x<width;x++)
        	{
                firstHalf=((N-J+1)/(N+1))*srcPixels[x][y];
                secondHalf=(J/(N+1))*destPixels[x][y];
                newVal=firstHalf+secondHalf;
                newVal=round(newVal);
                interVals[x][y]=newVal;
            }
        }
        output.setVals(interVals);
        output.Write(ostr);
        J++;
        //Memory Management
        for (int i = 0; i < width; i++) {
            delete []srcPixels[i];
        }
        delete [] srcPixels;
        for (int i = 0; i < width; i++) {
            delete []destPixels[i];
        }
        delete [] destPixels;
        //Memory Management
    }
    //Memory Management
    for (int i = 0; i < width; i++) {
        delete []interVals[i];
    }
    delete [] interVals;
    for (int i = 0; i < width; i++) {
        delete []imgVals1[i];
    }
    delete [] imgVals1;
    for (int i = 0; i < width; i++) {
        delete []imgVals2[i];
    }
    delete [] imgVals2;
    //Memory Management
    return true;
}

