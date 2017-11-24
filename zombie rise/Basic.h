#include"Graphics.h"
#include<list>
#pragma once
class Basic;
class Basic
{
public:
	Basic();
	~Basic();
	virtual void Collision() {};
	virtual void Update() {};
	virtual void Draw() {};
protected:
	Graphics* gfx;
	std::list<Basic>* basic;
	POINT position;
};

Basic::Basic()
{
}

Basic::~Basic()
{
	delete gfx;
	delete basic;
}
//void Basic::Collision() {};
//void Basic::Update() {};
//void Basic::Draw() {};