#ifndef GENERAL_IMAGE_HPP
#define GENERAL_IMAGE_HPP


#include"defines.hpp"


/////////////////////// image data /////////////////////////
//
//base class for image data
class CImageBase
{
	public:
	
		CImageBase(){}
		virtual ~CImageBase(){}
	
	
		virtual int Load(char* filepath){return 0;}
		virtual unsigned char* GetByteBuffer(){return 0;}
};


class CGdalImage: public CImageBase
{
	public:
		CGdalImage();
		~CGdalImage();
	
		int Load(char* filepath);
		unsigned char* GetByteBuffer();

	private:
		unsigned char* m_pByteBuffer;
};




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