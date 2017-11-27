#pragma once
#include"Basic.h"
#include"Graphics.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <list>
class GameLevel;
class GameLevel
{
public:
	GameLevel();
	~GameLevel();
	virtual void runGameLevel();
	
private:
	GameLevel* curentLevel;
};
GameLevel::GameLevel()
{

}
void GameLevel::runGameLevel() {

}
GameLevel::~GameLevel()
{

}