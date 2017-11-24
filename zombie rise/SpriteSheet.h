#pragma once
#include <wincodec.h>
#include "Graphics.h"
class SpriteSheet {
	Graphics* gfx;
	ID2D1Bitmap* bmp;
	public:
		SpriteSheet(wchar_t* filename, Graphics* gfx);
		~SpriteSheet();
		ID2D1Bitmap* getBitmap();
		void Draw();
		POINT position;
		float angle = 0;
		int rotation = 0;
		D2D1_POINT_2F imageCenter;
};