#pragma once
#include"Basic.h"
#include"Graphics.h"
#include <wincodec.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <list>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
class Animation
{
public:
	Animation(){};
	Animation(int time, std::wstring animationname, Graphics* gfx);
	~Animation();
	bool NextAnimetion();
	void Animate(D2D1_POINT_2F CenterPosition, int Rotation);
	std::vector<ID2D1Bitmap*>* GetImages();
	ID2D1Bitmap* loadImage(const wchar_t* filename);
	int countdown, time;
private:

	std::vector<int> sequence;
	std::vector<RECT> vRect;
	std::vector<ID2D1Bitmap*> imagesToAnimate;
	void loadImages(std::wstring animationname);
	int Rotation = 0;
	int Index = 0;
	
	
	Graphics* gfx;
	void readSequence(const std::wstring filepath);
	void readAnimations(const std::wstring filepath);
	void readBitmapsSize(const std::wstring animationname);
};
ID2D1Bitmap* Animation::loadImage(const wchar_t* filename) {
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
void Animation::loadImages(std::wstring animationname) {
	std::vector<wchar_t> bitmaps;
	readAnimations(animationname);
	readSequence(animationname);
	readBitmapsSize(animationname);
}
using namespace std;
void Animation::readSequence(const std::wstring animationname) {
	std::wstring filepath = animationname + L"\\sequence.txt";
	ifstream INFILE;
	INFILE.open(filepath);
	int current_number;
	sequence.clear();
	if (INFILE.is_open())
	{

		while (INFILE >> current_number) {
			sequence.push_back(current_number);
		}
	}
}

void Animation::readBitmapsSize(const std::wstring animationname) {
	std::wstring filepath = animationname + L"\\bitmapsSize.txt";
	ifstream INFILE;
	INFILE.open(filepath);
	int x, y, w, h;
	vRect.clear();
	if (INFILE.is_open())
	{

		while (INFILE >> x >> y >> w >> h) {
			vRect.push_back({ x,y,w,h });
		}
	}
}
void Animation::readAnimations(const std::wstring animationname) {
	std::wstring filepath = animationname + L"\\bitmaps.txt";
	ifstream INFILE;
	INFILE.open(filepath);
	string temp_char;
	RECT temp_rect;
	imagesToAnimate.clear();
	if (INFILE.is_open())
	{
		while (getline(INFILE, temp_char)) {
			wstring widestr = animationname+L"\\"+ wstring(temp_char.begin(), temp_char.end());
			const wchar_t* t = widestr.c_str();
			imagesToAnimate.push_back(loadImage(t));
			vRect.push_back(temp_rect);
		}
	}
}
std::vector<ID2D1Bitmap*>* Animation::GetImages() {
	return &imagesToAnimate;
}
bool Animation::NextAnimetion() {
	if (countdown == 0) {

		Index++;
		

		countdown = time;
		if (Index >= sequence.size()) {
			Index = 0; 
			return false;
		}
		
	}
	else countdown--;
	return true;
}
void Animation::Animate(D2D1_POINT_2F CenterPosition, int Rotation) {
	gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(Rotation, CenterPosition));
	ID2D1Bitmap* tempImage = imagesToAnimate[sequence[Index]];
	RECT rect = vRect[sequence[Index]];
	gfx->GetRenderTarget()->DrawBitmap(
		tempImage, D2D1::RectF(CenterPosition.x - rect.right, CenterPosition.y - rect.top, CenterPosition.x + rect.left, CenterPosition.y + rect.bottom), 1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f, tempImage->GetSize().width, tempImage->GetSize().height)
	);
	gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(0, CenterPosition));
}

Animation::Animation(int time, std::wstring animationname, Graphics* gfx)
{
	this->gfx = gfx;
	this->time = time;
	loadImages(animationname);
}

Animation::~Animation()
{
}