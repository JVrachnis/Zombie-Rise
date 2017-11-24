#pragma once
#include"Basic.h"
#include"Graphics.h"
#define _USE_MATH_DEFINES
#include <math.h>
class Player:public Basic
{
public:
	Player(Graphics* g, ID2D1Bitmap* body[17], ID2D1Bitmap* feet[8]);
	~Player();
	void Collision();
	void Update();
	void Draw();
	void Events();
	void GunAnimation();
	void FeetMovment();
	float angle;
	int bodyRotation=0;
	int feetRotation=0;
	int feetI=0, bodyI=0;
	int feetM=0,gun=1;
	bool gunFire=false;
	D2D1_POINT_2F CenterPosition;
	//POINT CenterPosition;
private:
	ID2D1Bitmap* body[17];
	ID2D1Bitmap* feet[8];
	
};
Player::Player(Graphics* g,ID2D1Bitmap* b[17],ID2D1Bitmap* f[8])
{
	gfx = g;
	CenterPosition.x =CenterPosition.y = 0;
	for (int i = 0; i < 17; i++)
	{
		body[i] = b[i];
	}
	for (int i = 0; i < 8; i++)
	{
		feet[i] = f[i];
	}
}

Player::~Player()
{
}
void Player::Collision() {

}
void Player::Update() {

	if (gunFire) { GunAnimation();
	}
	Events();
	Sleep(30);
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
void Player::FeetMovment() {
	
	if (feetI<7)
	{
		feetI++;
	}
	else feetI = 0;
}
void Player::GunAnimation() {
	if (gun==1)
	{
		bodyI++;
		if (bodyI>4)
		{
			bodyI = 1;
			gunFire = false;
		}
		Sleep(10);
	}else if (gun == 3)
	{
		bodyI++;
		if (bodyI > 10)
		{
			bodyI = 6;
			gunFire = false;
		}
		Sleep(30);
	}else if (gun == 4)
		{
			bodyI++;
			if (bodyI>13)
			{
				bodyI = 11;
				gunFire = false;
			}
			Sleep(30);
		}
	else if (gun == 5)
	{
		bodyI++;
		if (bodyI>16)
		{
			bodyI = 14;
			gunFire = false;
		}
		Sleep(30);
	}
}
void Player::Events() {
	if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState('A') & 0x8000)
	{
		CenterPosition.x -= 20;
		feetRotation = 180;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D') & 0x8000) {
		CenterPosition.x += 20;
		feetRotation = 0;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState('W') & 0x8000)
	{
		CenterPosition.y -= 20;

		feetRotation = 90;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState('S') & 0x8000) {
		CenterPosition.y += 20;
		feetRotation = -90;
		
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState('A') & 0x8000|| GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D') & 0x8000||
		GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState('W') & 0x8000|| GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState('S') & 0x8000) {
		FeetMovment();
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
	if (GetCursorPos(&p))
	{
		int x = CenterPosition.x;
		int y = CenterPosition.y;
		angle = atan2((p.y - y), (p.x - x));
		bodyRotation = (atan2((p.y - y), (p.x - x))) * 360 / (2 * M_PI);
	}
}