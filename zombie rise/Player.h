#pragma once
#include"Basic.h"
#include"bullet.h"

#define _USE_MATH_DEFINES
#include <math.h>
const float WINDOW_SIZE_X = 800;
const float WINDOW_SIZE_Y = 800;
class Player:public Basic
{
public:
	Player(Graphics* g, HWND windowhanle);
	~Player();
	void Collision();
	void Update();
	void Draw();
	bool gunFire=false;
	
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
	Animation* currentBody,* body,* gun1,* gun2,* gun3,* gun4,* gun5;
	Animation* feet;
	HWND hwnd;
};
Player::Player(Graphics* g, HWND windowhanle)
{
	gfx = g;
	this->entities = entities;
	CenterPosition.x =CenterPosition.y = 0;
	body = new Animation(1,L"bodyAnimation", gfx);
	gun1 = new Animation(1, L"gun1Animation", gfx);
	currentBody = body;
	feet = new Animation(1,L"feetAnimation", gfx);
	hwnd = windowhanle;
	items = new list<Basic*>() ;
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
	feet->Animate(CenterPosition, feetRotation);
	currentBody->Animate(CenterPosition, bodyRotation);
	
}
void Player::FeetMovment(int x, int y) {

	CenterPosition.x += x;
	CenterPosition.y += y;
	feet->NextAnimetion();
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
		bodyI = 1;
		gunFire = currentBody->NextAnimetion();	
		if (!gunFire) {

			POINT p;
			RECT r;
			float angleT;
			if (GetCursorPos(&p))
			{
				if (ScreenToClient(hwnd, &p))
				{
					int x = CenterPosition.x;
					int y = CenterPosition.y;
					angleT = atan2((25), (53));
					items->push_back(new Bullet(gfx, hwnd, { CenterPosition.x + 53*cos(angleT) * cos(angle),CenterPosition.y + (25/sin(angleT)) * sin(angle) }, bodyRotation));
				}
			}
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
		moveX = -1;
	}
	if (CenterPosition.x + 30<WINDOW_SIZE_X)
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D') & 0x8000) {
		moveX = 1;
	}
	if (CenterPosition.y-30>0) 
		if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState('W') & 0x8000)
		{
			moveY = -1;
		}
	
	if (CenterPosition.y + 30<WINDOW_SIZE_Y)
	if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState('S') & 0x8000) {
		moveY = 1;
	}
	if (moveY != 0 || moveX != 0) {
		float angleT = atan2((moveY), (moveX));
		feetRotation =  angleT* 360 / (2 * M_PI);
		FeetMovment(10 * cos(angleT), 10* sin(angleT));
	}
	else {
		FeetStop();
	}

		
	if ((GetKeyState(VK_LBUTTON) & 0x100)) {
		gunFire = true;
	}

	if (GetAsyncKeyState('1') & 0x8000)
	{
		currentBody = gun1;
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
		if (ScreenToClient(hwnd, &p))
		{
			int x = CenterPosition.x;
			int y = CenterPosition.y;
			angle = atan2((p.y - y), (p.x - x));
			bodyRotation = (atan2((p.y - y), (p.x - x))) * 360 / (2 * M_PI);
		}
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