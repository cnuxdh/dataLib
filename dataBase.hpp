#ifndef GENERAL_IMAGE_HPP
#define GENERAL_IMAGE_HPP

#include"stdlib.h"

#include"defines.hpp"



enum
{
/* 8bit, gray */
    CV_LOAD_IMAGE_GRAYSCALE  =0,
/* color */
    CV_LOAD_IMAGE_COLOR      =1,
};


////////////////// Matrix Data  ///////////////////
class CMat
{
	public:
		
		CMat();
		CMat(unsigned char* pSrc, int rows, int cols, int dims);
		
		~CMat();
		
		
		//create byte matrix
		int Create(int row, int col);
	  
	  
	  //get data buffer
	  unsigned char* GetBuffer();
	  
	  //get the dimensions
	  int GetRows();
	  int GetCols();
	  int GetDims();
		
		//operator override
		CMat& operator =(CMat& m);
		
		//counter for memory management
		int m_nCounter; 
		
	private:
		unsigned char* m_pBuffer;
		int m_nRows,m_nCols; 
		int m_nDims; 
		CMat* m_pSrc; //pointer to the source image invoked by 'operator ='
};

inline CMat::CMat()
{
	m_pBuffer = NULL;
	m_nRows = 0;
	m_nCols = 0;
	m_nDims = 0;
	m_pSrc = NULL;
	m_nCounter = 0;
}
inline CMat::CMat(unsigned char* pSrc, int rows, int cols, int dims)
{
	m_pBuffer = NULL;
	m_nRows = 0;
	m_nCols = 0;
	m_nDims = 0;
	m_pSrc = NULL;
	m_nCounter = 0;
	
	if(pSrc!=NULL)
	{
		m_pBuffer = (unsigned char*)malloc(rows*cols*dims);
		memcpy(m_pBuffer, pSrc, rows*cols*dims);
		m_nRows = rows;
		m_nCols = cols;
		m_nDims = dims;
	}	
}
inline CMat::~CMat()
{ 
	printf("CMat counter: %d \n", m_nCounter);
		 
	if(m_nCounter==0)
	{
		printf("Release Mat memory ... \n");
		free(m_pBuffer);
	}
	
	if( m_pSrc!=NULL)
		m_pSrc->m_nCounter--;	
}
inline unsigned char* CMat::GetBuffer()
{
	return m_pBuffer;
}	
inline int CMat::GetRows()
{
	return m_nRows;
}	
inline int CMat::GetCols()
{
	return m_nCols;
}	
inline int CMat::GetDims()
{
	return m_nDims;
}	
inline CMat& CMat::operator=(CMat& m)
{
	 printf("[CMat operator ==] ... \n");   
	 
	 if( this != &m )
   {
   		//save the pointer
   		m_pSrc = &m;
			
   		m.m_nCounter ++;
   		
   		m_nCounter = m.m_nCounter;
   		m_pBuffer  = m.GetBuffer();
   		m_nRows = m.GetRows();
   		m_nCols = m.GetCols();	
   		m_nDims = m.GetDims();
   }
   
   return *this;
}
////////////////////////////////////////////////////////////////






/////////////////////// image data /////////////////////////
//
//base class for image data
class CImageBase
{
	public:
	
		CImageBase(){}
		virtual ~CImageBase(){}
	
	
		virtual int Load(char* filepath, int flags){return 0;}
		virtual int Write(char* filepath, 
			unsigned char* pImage, int ht, int wd, int nChannels){return 0;}
		
		virtual unsigned char* GetByteBuffer(){return 0;}
		virtual int GetImageHt(){return 0;}
		virtual int GetImageWd(){return 0;}
		virtual int GetChannels(){return 0;}
		//Mat& operator = (const Mat& m);
};
class CGdalImage: public CImageBase
{
	public:
		CGdalImage();
		~CGdalImage();
	
		int Load(char* filepath, int flags);
		int Write(char* filepath, 
			unsigned char* pImage, int ht, int wd, int nChannels);
		
		unsigned char* GetByteBuffer();
		int GetImageHt(){return m_ht;}
		int GetImageWd(){return m_wd;}
		int GetChannels(){return m_nChannels;}
		
	private:
		unsigned char* m_pByteBuffer;
		int m_ht,m_wd;
		int m_nChannels;
		//int m_nCounter; //counter for memory management
};




//
CMat ImageRead(char* filepath, int flags);
int  ImageWrite(char* filepath, CMat& image);







////////////////////// feature data //////////////////////////
//base class for feature point data
class CPointFeatureBase
{
	public:
		CPointFeatureBase(){}
		virtual ~CPointFeatureBase(){}
		
		virtual int Read(char* filepath, ImgFeature& imgFeat) {return 0;}
		virtual int Write(char* filepath, ImgFeature& imgFeat){return 0;}
};


class CSiftFeatureDataBinary: public CPointFeatureBase
{
	public:
		CSiftFeatureDataBinary();
		~CSiftFeatureDataBinary();

		
		int Read(char* srcPath, ImgFeature& imgFeat);
		int Write(char* dstPath, ImgFeature& imgFeat);

};




#endif