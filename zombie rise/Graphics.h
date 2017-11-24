#pragma once
#include <Windows.h>
#include <d2d1.h>
class Graphics
{
public:
	Graphics();
	~Graphics();
	bool Init(HWND windowHandle);
	ID2D1RenderTarget* GetRenderTarget() { return renderTarget; };
	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }
	void ClearScreen(float r, float g, float b);
	void DrawCircle(float y, float x, float radius, float r, float g, float b, float a);
	void DrawRectangle(float y, float x, float width, float height, float r, float g, float b, float a);
private:
	ID2D1SolidColorBrush* brush;
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
};