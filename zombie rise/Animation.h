#pragma once
#include"Basic.h"
#include"Graphics.h"
#include <wincodec.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <list>
#include <vector>

class Animation
{
public:
	Animation();
	~Animation();
	void Animate(POINT center);
	ID2D1Bitmap* loadImage(wchar_t* filename);
	void loadImages(std::string animationname);
private:
	std::vector<ID2D1Bitmap>* imagesToAnimate;
	int Rotation = 0;
	int Index = 0;
	std::vector<int>* steps;
	RECT position;
	Graphics* gfx; 
	template<typename T>
	vector<T> readFrom(const std::string& filepath);
};
ID2D1Bitmap* Animation::loadImage(wchar_t* filename) {
	ID2D1Bitmap* bmp = NULL;
	HRESULT hr;
	IWICImagingFactory *wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory, NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);
	IWICBitmapDecoder *wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder);
	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);
	IWICFormatConverter *wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom
	);
	gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(wicConverter, NULL, &bmp);
	if (wicFactory)wicFactory->Release();
	if (wicDecoder)wicDecoder->Release();
	if (wicConverter)wicConverter->Release();
	if (wicFrame)wicFrame->Release();
	return bmp;
}
void Animation::loadImages(std::string animationname) {

}

template<typename T>
vector<T> Animation::readFrom(const std::string& filepath) {
	vector<T> newVector;
	ifstream INFILE(filepath, std::ios::in | std::ifstream::binary);
	istreambuf_iterator iter(INFILE);
	copy(iter.begin(), iter.end(), std::back_inserter(newVector));
	return newVector;
}

void Animation::Animate(POINT center) {

}

Animation::Animation()
{
}

Animation::~Animation()
{
}