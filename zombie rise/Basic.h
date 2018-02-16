
#pragma once
#include"Graphics.h"
#include<list>
#include"Animation.h"
#define _USE_MATH_DEFINES
#include <math.h>
class Basic;
class Basic
{
public:
	Basic();
	~Basic();
	virtual void Collision() {};
	virtual void Update() {};
	virtual void Draw() {};
	std::list<Basic*>* items;
protected:
	Graphics* gfx;

	D2D1_POINT_2F CenterPosition;
	POINT position;
};

Basic::Basic()
{
}

Basic::~Basic()
{
	delete gfx;
	delete items;
}
//void Basic::Collision() {};
//void Basic::Update() {};
//void Basic::Draw() {};