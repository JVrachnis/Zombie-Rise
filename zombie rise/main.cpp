#include<Windows.h>
#include <wincodec.h>
#include"Graphics.h"
#include <cstring>
#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#define _USE_MATH_DEFINES
#include <math.h>
#include "SpriteSheet.h"
#include"Basic.h"
#include"Player.h"
using namespace std;
ID2D1Bitmap*Zombie;
ID2D1Bitmap* makeImage(wchar_t* filename);
list<Basic*> items;
bool initialazed=false;
Graphics* graphics;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_DESTROY) { PostQuitMessage(0); return 0; }
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE prevInstance,LPWSTR cmd,int nCmdShow) 
{
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = "MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&windowclass);

	RECT rect = {0,0,(long)WINDOW_SIZE_X,(long)WINDOW_SIZE_Y };
	AdjustWindowRectEx(&rect,WS_OVERLAPPEDWINDOW,false,WS_EX_OVERLAPPEDWINDOW);
	HWND windowhanle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,"MainWindow","Test!!",WS_OVERLAPPEDWINDOW,0,0,rect.right-rect.left,rect.bottom-rect.top,NULL,NULL,hInstance,0);
	if (!windowhanle)return -1;
	ShowWindow(windowhanle, nCmdShow);
	graphics = new Graphics();
	if (!graphics->Init(windowhanle)) {
		delete graphics;
		return -1;
	}
	MSG message;
	message.message = WM_NULL;
	//SpriteSheet* Zombie = new SpriteSheet(L"Zombie.png", graphics);
	Basic* Me = new Player(graphics,windowhanle);
	items.push_back(Me);
	list<Basic*> newItems;
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) { DispatchMessage(&message); }
		graphics->BeginDraw();
		graphics->ClearScreen(0.2f, 0.4f, 0.8f);
		for each (Basic* item in items)
		{
			item->Update();
			if ((item->items)!=NULL) {
				newItems.merge(*(item->items));
				item->items->clear();
			}
		}
		for each (Basic* item in items)
		{
			item->Draw();
		}
		items.merge(newItems);
		newItems.clear();
		Me->Draw();
		graphics->EndDraw();
	}
	delete graphics;
	return 0;
}
ID2D1Bitmap* makeImage(wchar_t* filename) {
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
	graphics->GetRenderTarget()->CreateBitmapFromWicBitmap(wicConverter, NULL, &bmp);
	if (wicFactory)wicFactory->Release();
	if (wicDecoder)wicDecoder->Release();
	if (wicConverter)wicConverter->Release();
	if (wicFrame)wicFrame->Release();
	return bmp;
}