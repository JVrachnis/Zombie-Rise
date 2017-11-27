#pragma once
#include"Basic.h"
#include"Graphics.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <list>
const float WINDOW_SIZE_X = 800;
const float WINDOW_SIZE_Y = 800;
class Player:public Basic
{
public:
	Player(Graphics* g, ID2D1Bitmap* body[17], ID2D1Bitmap* feet[8], HWND windowhanle);
	~Player();
	void Collision();
	void Update();
	void Draw();
	bool gunFire=false;
	D2D1_POINT_2F CenterPosition;
	//POINT CenterPosition;
private:
	void Events();
	void GunAnimation();
	void FeetMovment(int x, int y);
	void FeetStop();
	float angle;
	int bodyRotation = 0;
	int feetRotation = 0;
	int feetI = 0, bodyI = 0;
	int feetM = 0, gun = 0;
	long time = 0, timeMove = 0, timeStop = 0, timeGun = 0;
	std::list<Basic>* entities;
	ID2D1Bitmap* body[17];
	ID2D1Bitmap* feet[8];
	HWND hwnd;
	
};
Player::Player(Graphics* g,ID2D1Bitmap* b[17],ID2D1Bitmap* f[8], HWND windowhanle)
{
	gfx = g;
	this->entities = entities;
	CenterPosition.x =CenterPosition.y = 0;
	for (int i = 0; i < 17; i++)
	{
		body[i] = b[i];
	}
	for (int i = 0; i < 8; i++)
	{
		feet[i] = f[i];
	}
	hwnd = windowhanle;
}

Player::~Player()
{
}
void Player::Collision() {

}
void Player::Update() {

	if (gunFire) { GunAnimation();
	}
	if(hwnd == GetForegroundWindow())Events();
	time++;
}
void Player::Draw() {
	gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(feetRotation, CenterPosition));
	gfx->GetRenderTarget()->DrawBitmap(
		feet[feetI], D2D1::RectF(CenterPosition.x - feet[feetI]->GetSize().width/2, CenterPosition.y - feet[feetI]->GetSize().height/2, CenterPosition.x + feet[feetI]->GetSize().width/2, CenterPosition.y + feet[feetI]->GetSize().height/2), 1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f, feet[feetI]->GetSize().width, feet[feetI]->GetSize().height)
	);

	gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(bodyRotation, CenterPosition));
	gfx->GetRenderTarget()->DrawBitmap(
		body[bodyI], D2D1::RectF(CenterPosition.x- body[0]->GetSize().width/2, CenterPosition.y- body[0]->GetSize().height/2, CenterPosition.x+ body[bodyI]->GetSize().width - body[0]->GetSize().width / 2, CenterPosition.y + body[bodyI]->GetSize().height-body[0]->GetSize().height /2), 1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f, body[bodyI]->GetSize().width, body[bodyI]->GetSize().height)
	);
	gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(0, CenterPosition));
}
void Player::FeetMovment(int x,int y) {
		if (feetI < 7)
		{
			if (time - timeMove >= 5) {
				feetI++;
				timeMove = time;
				CenterPosition.x += x;
				CenterPosition.y += y;
			}
		}
		else feetI = 0;
		
}
void Player::FeetStop() {
	if (time-timeStop >= 5) {
		if (feetI != 0 && feetI != 4) {
			feetI--;
			timeStop = time;
		}
		
	}
}
void Player::GunAnimation() {
	if (gun==1)
	{
		if (time - timeGun >= 5) {
			bodyI++;
			if (bodyI > 4)
			{
				bodyI = 1;
				gunFire = false;
			}
			timeGun = time;
		}
	}else if (gun == 3)
	{
		if (time - timeGun >= 6) {
			bodyI++;
			if (bodyI > 10)
			{
				bodyI = 6;
				gunFire = false;
			}
			timeGun = time;
		}
	}else if (gun == 4)
		{
		if (time - timeGun >= 20) {
			bodyI++;
			if (bodyI > 13)
			{
				bodyI = 11;
				gunFire = false;
			}
			timeGun = time;
		}
	}
	else if (gun == 5)
	{
		if (time - timeGun >= 15) {
			bodyI++;
			if (bodyI > 16)
			{
				bodyI = 14;
				gunFire = false;
			}
			timeGun = time;
		}
	}
}
void Player::Events() {
	int moveY = 0, moveX = 0;
	if (CenterPosition.x - 30>0)
	if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState('A') & 0x8000)
	{
		moveX = -20;
	}
	if (CenterPosition.x + 30<WINDOW_SIZE_X)
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D') & 0x8000) {
		moveX = 20;
	}
	if (CenterPosition.y-30>0) 
		if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState('W') & 0x8000)
		{
			moveY = -20;
		}
	
	if (CenterPosition.y + 30<WINDOW_SIZE_Y)
	if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState('S') & 0x8000) {
		moveY = 20;
	}
	if (moveY != 0 || moveX != 0) {
		float angleT = atan2((moveY), (moveX));
		feetRotation =  angleT* 360 / (2 * M_PI);
		FeetMovment(20 * cos(angleT), 20 * sin(angleT));
	}
	else {
		FeetStop();
	}

		
	if ((GetKeyState(VK_LBUTTON) & 0x100)) {
		gunFire = true;
	}

	if (GetAsyncKeyState('1') & 0x8000)
	{
		gun = 1;
		bodyI = 1;
	}else if(GetAsyncKeyState('2') & 0x8000)
	{
		gun = 2;
		bodyI = 5;
	}else if (GetAsyncKeyState('3') & 0x8000)
	{
		gun = 3;
		bodyI = 6;
	}else if (GetAsyncKeyState('4') & 0x8000)
	{
		gun = 4;
		bodyI = 11;
	}
	else if (GetAsyncKeyState('5') & 0x8000)
	{
		gun = 5;
		bodyI = 14;
	}
	POINT p;
	RECT r;
	if (GetCursorPos(&p))
	{
		GetWindowRect(hwnd,&r);
		p.x -= r.left;
		p.y -= r.top;
		int x = CenterPosition.x;
		int y = CenterPosition.y;
		angle = atan2((p.y - y), (p.x - x));
		bodyRotation = (atan2((p.y - y), (p.x - x))) * 360 / (2 * M_PI);
	}
	/*
	this was realy slow
	MSG message;
	message.message = WM_NULL;
	if (GetMessage(&message, NULL, 0, 0) > 0) {
		switch (message.message)
		{
		case(WM_MOUSEMOVE): {
			POINT p;
			p.x = LOWORD(message.lParam);
			p.y = HIWORD(message.lParam);
			int x = CenterPosition.x;
			int y = CenterPosition.y;
			angle = atan2((p.y - y), (p.x - x));
			bodyRotation = (atan2((p.y - y), (p.x - x))) * 360 / (2 * M_PI);
			break;
		}
		case(WM_KEYDOWN): {
			if (message.wParam == 'A')
			{
				CenterPosition.x -= 20;
				feetRotation = 180;
			}
			if (message.wParam == 'D') {
				CenterPosition.x += 20;
				feetRotation = 0;
			}
			if (message.wParam == 'W')
			{
				CenterPosition.y -= 20;

				feetRotation = 90;
			}
			if (message.wParam == 'S') {
				CenterPosition.y += 20;
				feetRotation = -90;
			}
			FeetMovment();
			break;
		}
		case(PM_REMOVE):DispatchMessage(&message);
		default:
			break;
		}
	}*/
}