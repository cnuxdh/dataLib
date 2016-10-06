

#include"dataBase.hpp"


//gdal header file
#include"geotiff.h"




CGdalImage::CGdalImage()
{
	m_pByteBuffer = NULL;
	m_nCounter = 0;
}


CGdalImage::~CGdalImage()
{
	
	free(m_pByteBuffer);
	//printf("[CGdalImage]: release memory ! \n");
	
}


int CGdalImage::Load(char* filepath, int flags)
{
  
  //
  int nChannels = 0;
  
  stGeoInfo geoinfo;
  ReadGeoFile(filepath, geoinfo);
  nChannels = geoinfo.nband;
  
  m_nRows = geoinfo.ht;
  m_nCols = geoinfo.wd;
  m_nChannels = nChannels; 
  
  m_pByteBuffer = (unsigned char*)malloc(m_nRows*m_nCols*m_nChannels);
  
  //gray image
  if(flags==0)
  {
  	
  	if(nChannels==1)
  	{
  			unsigned char* pGray = NULL;
  			int ht,wd;
  			ReadGeoFileByte(filepath, 0, &pGray, ht, wd);
  			
  			assert(  (m_nRows==ht) && (m_nCols==wd) ) ;
  			
  			memcpy(m_pByteBuffer, pGray, ht*wd);
  			
  			free(pGray);
  	}
  	else if(nChannels==3)
  	{
  			unsigned char* pRed = NULL;
  			unsigned char* pGreen = NULL;
  			unsigned char* pBlue = NULL;
  			int ht,wd;
  			
  			ReadGeoFileByte(filepath, 2, &pRed, ht, wd);
  			
  			assert(  (m_nRows==ht) && (m_nCols==wd) ) ;
  			
  			memcpy(m_pByteBuffer, pRed, ht*wd);
  			
  			free(pRed);
  			free(pGreen);
  			free(pBlue);
  	}
  }
  else if(flags==1) //color image
  {	
  	if(nChannels==1)
  	{
  			unsigned char* pGray = NULL;
  			int ht,wd;
  			ReadGeoFileByte(filepath, 0, &pGray, ht, wd);
  			
  			assert(  (m_nRows==ht) && (m_nCols==wd) ) ;
  			
  			memcpy(m_pByteBuffer, pGray, ht*wd);
  			memcpy(m_pByteBuffer+ht*wd, pGray, ht*wd);
  			memcpy(m_pByteBuffer+ht*wd*2, pGray, ht*wd);
  			
  			free(pGray);
  	}
  	else if(nChannels==3)
  	{
  			unsigned char* pRed = NULL;
  			unsigned char* pGreen = NULL;
  			unsigned char* pBlue = NULL;
  			int ht,wd;
  			
  			ReadGeoFileByte(filepath, 0, &pBlue, ht, wd);
  			ReadGeoFileByte(filepath, 1, &pGreen, ht, wd);
  			ReadGeoFileByte(filepath, 2, &pRed, ht, wd);
  			
  			assert(  (m_nRows==ht) && (m_nCols==wd) ) ;
  			
  			memcpy(m_pByteBuffer, pBlue, ht*wd);
  			memcpy(m_pByteBuffer+ht*wd, pGreen, ht*wd);
  			memcpy(m_pByteBuffer+ht*wd*2, pRed, ht*wd);
  			
  			free(pRed);
  			free(pGreen);
  			free(pBlue);
  	}
  }
  		
	return 0;
}


unsigned char* CGdalImage::GetByteBuffer()
{
	return m_pByteBuffer;	
}


//generate bytemat from image
CByteMat& ImageRead(char* filepath, int flags)
{
	
	CImageBase* pImage = new CGdalImage();
	pImage->Load(filepath, flags);
	
	CByteMat byteMat( pImage->GetByteBuffer(), 
		pImage->GetImageHt(), 
		pImage->GetImageWd(),
		pImage->GetChannels()
		);
	
	delete pImage;
	
	return byteMat;
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