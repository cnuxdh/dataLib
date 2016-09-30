

#include"dataBase.hpp"


//gdal header file




CGdalImage::CGdalImage()
{
	
}


CGdalImage::~CGdalImage()
{
	
}


int CGdalImage::Load(char* filepath)
{
  
  
  
  
		
	return 0;
}



/////////////////////// CSiftFeatureDataBinary /////////////////////
CSiftFeatureDataBinary::CSiftFeatureDataBinary()
{

}

CSiftFeatureDataBinary::~CSiftFeatureDataBinary()
{

}


int CSiftFeatureDataBinary::Read(char* srcPath, ImgFeature& imgFeat)
{
	
	
	
	return 0;
}
		

int CSiftFeatureDataBinary::Write(char* dstPath, ImgFeature& imgFeat)
{
	
	FILE* fp = fopen(dstPath, "wb");
	if(fp == NULL)
		return 0;

	//number of feature points
	int nFeat = imgFeat.featPts.size();
	fwrite(&nFeat, sizeof(int), 1, fp );	
	
	//the dim of feature 
	int ndim = 128;
	fwrite(&ndim, sizeof(int), 1, fp); 
	   
	//write feature vector one by one
	for(int i=0; i<nFeat; i++)
	{
		//y x scale orientation
		float y,x,scale,ori;
		x = imgFeat.featPts[i].x; 
		y = imgFeat.featPts[i].y;
		scale = imgFeat.featPts[i].scl;
		ori   = imgFeat.featPts[i].ori;
		
		fwrite(&y, sizeof(float), 1, fp);
		fwrite(&x, sizeof(float), 1, fp);
		fwrite(&scale, sizeof(float), 1, fp);
		fwrite(&ori, sizeof(float), 1, fp);
		
		//feature vector
    fwrite( &(imgFeat.featPts[i].feat[0]), sizeof(float), 128, fp);
	}
	fclose(fp);
	
	return 0;
}