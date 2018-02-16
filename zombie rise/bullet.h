#pragma once
#include"Basic.h"

class Bullet:public Basic 
{
public:
	Bullet(Graphics* g, HWND windowhanle, D2D1_POINT_2F CenterPosition,int rotation);
	~Bullet() {};
	void Collision() {};
	void Update();
	void Draw();

private:
	Animation * animation;
	int rotation;
};
Bullet::Bullet(Graphics* g, HWND windowhanle, D2D1_POINT_2F CenterPosition, int rotation) {
	this->gfx = g;
	this->CenterPosition = CenterPosition;
	this->rotation = rotation;
	animation = new Animation(1, L"bulletAnimation", gfx);
}
void Bullet::Update() {
	float angleT=rotation*(2 * M_PI)/360;
	CenterPosition.x += 10 * cosf(angleT);
	CenterPosition.y += 10 * sinf(angleT);
}
void Bullet::Draw() {
	animation->Animate(CenterPosition, rotation);
}
